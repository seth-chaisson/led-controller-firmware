/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"
#include "uart.h"


/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{

    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    ANSELA= 0b00001000;
    TRISA = 0b00001000; // ra0-2 status led
                        // ra 3 touch analog input
    PORTA = 0;

    ANSELD =0;
    TRISD = 0b00000000; // rd7 clock
                        // rd6 data
                        // rd5 clear
    PORTD =0b00000000;

    TRISE = 0b00000101; // re 0 and 2 analog touch input
    PORTE =0;

    ANSELB = 0b00111111;
    TRISB = 0b11111111; // rb 0-5 analog touchinput
    PORTB = 0;

    TRISC = 0b10111111;
    PORTC = 0;



//Timer0 Registers Prescaler= 8 - TMR0 Preset = 0 - Freq = 976.56 Hz - Period = 0.001024 seconds
T0CS = 0;  // bit 5  TMR0 Clock Source Select bit...0 = Internal Clock (CLKO) 1 = Transition on T0CKI pin
T0SE = 0;  // bit 4 TMR0 Source Edge Select bit 0 = low/high 1 = high/low
PSA = 0;   // bit 3  Prescaler Assignment bit...0 = Prescaler is assigned to the Timer0
PS2 = 0;   // bits 2-0  PS2:PS0: Prescaler Rate Select bits
PS1 = 0;
PS0 = 0;
TMR0 = 0;             // preset for timer register






T1CON = 0b00110101; // set timer 1 to  tick = 1 us; fosc/;4 /8
TMR1 = 0;
TMR1IE =0;




UART_Init();


}

