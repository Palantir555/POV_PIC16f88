/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <string.h>
#include <stdio.h>

#define RECEIVED_CHAR RCIF
#define INPUT_REGISTER RCREG
#define SENT_CHAR TXIF

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12
extern char UART_buff[50];
extern bool newStrFlag;

void interrupt isr(void)
{
    char ch;
    TMR0IF=0;
    INT0IF=0;
    //RBIF=0;
    //PIR1=0x00;

    if(SENT_CHAR)
    {
        TXIE=0;
        SENT_CHAR=0;
    }

    if(RECEIVED_CHAR)
    {
        ch = INPUT_REGISTER; //This also clears the flag RCIF
        if(ch == '$')
            strcpy(UART_buff, "");
        else if(ch == '#')  //String terminator
            newStrFlag = 1;
        else
        {
            int len=strlen(UART_buff);
            sprintf(UART_buff, "%c", &ch);
        }
    }
}
#endif