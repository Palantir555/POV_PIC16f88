/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "main.h"

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif
#include <string.h>
#include <stdint.h>     /* For uint8_t definition */
#include <stdbool.h>    /* For true/false definition */
#include "system.h"     /* System funct/params, like osc/peripheral config */
#include "dic.c"        /* A dictionary with the letters and combinations */

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & BOREN_ON & LVP_ON &
        CPD_OFF & WRT_OFF & CCPMX_RB0 & CP_OFF);
__CONFIG(FCMEN_OFF & IESO_ON);

#define _XTAL_FREQ 8000000
#define EEPROM_DELAY 10
#define MAX_DELAY 35  //Max delay for __delay_ms()
#define maxOutputLen 11



void delay(long int ms);
void writeOutput(char *ch);
void showCh(char *ch);
unsigned int getRevTime(void);
void waitForRevStart(void);
void changeOutStr(char *str);
char* findLetterInDict(char *letter);

//int maxOutputLen;
char UART_buff[50]; //not maxOutputLen+1 in case you want to use multiple revolutions
char outputStr[50];
bool newStrFlag;
int revTime_ms;

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    ConfigurePorts();
    ConfigureRegisters();
    //maxOutputLen = 11;
    char *ch;
    char _NOTFOUND[9] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, '\0'};
    waitForRevStart();
    delay(50);
    waitForRevStart();
    getRevTime();
    strcpy(outputStr, "HELLO");
    int i=0;
    while(1)
    {
        waitForRevStart();
        for(i=0; i<strlen(outputStr); i++)
        {
            ch=findLetterInDict(outputStr+(i*sizeof(char)));
            if(ch == 0x00)
                showCh(_NOTFOUND);
            else
                showCh(ch);
        }

        if(newStrFlag)
            changeOutStr(UART_buff);
        //showCh(_H);
        //showCh(_E);
        //showCh(_L);
        //showCh(_L);
        //showCh(_O);
        /*
        ch = 0xff;
        writeOutput(&ch);
        delay(revTime_ms);
        ch = 0x00;
        writeOutput(&ch);
        delay(1000);
         */
    }
}

void writeOutput(char *ch)
{
    char ch_copy = *ch;
    ch_copy &= 0b11011111; //Not wanna write to the MCLR pin. Necessary?? #!#
    PORTA = ch_copy;
    RB0 = (*ch >> 5) & 1; //Write to PORTB, bit0 the missing bit.
}

void showCh(char *ch)
{
    int i=0;
    int len=8;
    int t=(revTime_ms/maxOutputLen)/len;
    for(i=0; i<len; i++)
    {
        writeOutput(ch+(i*sizeof(char)));
        delay(t);
    }
}

unsigned int getRevTime(void)
{
    int cnt=0;
    waitForRevStart();
    while(RB4 == 1)
        delay(10);
    while(RB4 == 0)
        delay(10);

    while(RB4 == 1)
    {
        delay(25);
        cnt++;
    }

    revTime_ms = cnt*25;

    //tst:
    //revTime_ms=1500;
    //endtst
    return(revTime_ms);
}

void waitForRevStart(void)
{
    //while(RB4 == 0);
    writeOutput(0x00);
    while(RB4 == 1);
        //delay(10);
    //delay(80);
}

void delay(long int ms)
{
    while(ms > MAX_DELAY)
    {
        __delay_ms(MAX_DELAY);
        ms -= MAX_DELAY;
    }
    while(ms > 0)
    {
        __delay_ms(1);
        ms -= 1;
    }
}

void changeOutStr(char *str)
{
    if(newStrFlag)
    {
        newStrFlag=0;
        strcpy(outputStr, UART_buff);
        strcpy(UART_buff, ""); //clear the buffer.
    }
}

char* findLetterInDict(char *letter)
{
    for(int i=0; i<9; i++)
    {
        if(dictionary[i][0] == *letter)
            return(&dictionary[i][0]+(1*sizeof(char)));
    }
    return(0x00); //letter not found in the dict
}