/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

void ConfigureOscillator(void)
{
    OSCCON = 0x72; //Clock at 8MHz
}

void ConfigurePorts(void)
{
    ANSEL = 0x00; //Nothing analog
    TRISA &= 0b00100000;
    TRISB &= 0b11111010;    //TRISB<0> as an output to be used as RA5
    TRISB |= 0b00110000;    //TRISB<5,2> set for the UART.
                            //  TRISB<4> as input for the sensor
    OPTION_REG = 0x00;  //PORTB Pull-ups enabled
}

void ConfigureRegisters(void)
{
    //SPEN = 1; //RCSTA<7> set for the UART
    INTCON = 0b11000000;  //Disabled interrupts on PORTB, but enabled globally
    TXSTA = 0b00100110; //bit2=1 -> High speed. Might need to change it
    RCSTA = 0b10010000;

    //Serial port:
    SPBRG = 51;
    BRGH = 1;
    SYNC = 0;   //Disable synchronous
    SPEN = 1;   //Enable asynchronous
    //INTCON |= 0b11000000; //Because we are using interrrupts
    //    Transmit:
    TXIE = 0;   //TX interrupts are disabled until we need to send something.
    TX9 = 0;    //8 bits
    TXEN = 0;   //Disable transmission.
    //TXEN = 1;   //Enable transmission. Loading data to the TXREG register will start the transmission.
    //    Receive:
    RCIE = 1;   //Enable interrupts for RX
    RX9 = 0;    //8 bits
    CREN = 1;   //Enable reception. Loading data to the TXREG register will start the transmission.
                //  Flag RCIF will be set when reception is complete and an interrupt will be generated (if enabled)
                //  read the 8-bit received data by reading the RCREG register.
    RCIF = 0;
    TXIF = 0;
}