/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#define _XTAL_FREQ 32000000

#include "mTouch/mTouch.h"
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "sine.c"
#include "uart.h"

#define CLOCK_ON portd_shadow |= 0b10000000 ;
#define DATA_ON  portd_shadow |= 0b01000000 ;
#define CLEAR_ON portd_shadow |= 0b00100000 ;

#define CLOCK_OFF portd_shadow &= 0b01111111 ;
#define DATA_OFF  portd_shadow &= 0b10111111 ;
#define CLEAR_OFF portd_shadow &= 0b11011111 ;

#define WRITE_PORT PORTD = portd_shadow;__delay_us(50);


#define STATUS_RED   RA0
#define STATUS_BLUE  RA1
#define STATUS_GREEN RA2


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

void send_led_data(); // sends the 30 bit led data out the shift register
void set_led(unsigned char,unsigned char); //turn on light(1-10), as color(0b000)[red,green,blue]

/* i.e. uint8_t <variable_name>; */

unsigned int count =0;
unsigned char portd_shadow=0;
unsigned long led_data =0;
unsigned char byte_count @ 0x020;
unsigned char temp @ 0x030;
unsigned char a[162] @ 0xa0 ;
unsigned char enable = 1;
//unsigned char a2[80] @ 0x120 ;


unsigned char led_number =54;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    //printf("reset");
    //putch(0x0d);
    //putch(0x0a);

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

   // mTouch_Init();                  // mTouch Initialization (Required)

    GIE =0;
    //__delay_ms(5000);
    printf("--------------------------- \n \n program initilaized \n \n");


    /*
     if uart_read = a next 3 bytes get copied to all led
                  = s next byte is led number 3 after that are rgb value

     */

     


     
        unsigned int loop_count = 0;
    while(1)
    {
        byte_count = (led_number*3);

        char recived_byte = UART_Read_No_Block();

        if(recived_byte == 0xff)
        {
            for(unsigned char x=0; x< (led_number*3); x+=3)
            {
                a[x]   = 255;
                a[x+1] = 255;
                a[x+2] = 255;
            }
            recived_byte = 0;
        }


unsigned char temp_red,temp_green, temp_blue, led_index;

    switch(recived_byte)
    {
        case 0://
            continue;
        case 's': // sending s will take 1 byte as an led address and 3 as color
            led_index = UART_Read(); 
            
            a[led_index+1] = UART_Read();
            a[led_index]   = UART_Read();
            a[led_index+2] = UART_Read();
            break;
        case 'a': // sending a will copy the next 3 bytes GRB to all of the leds

            temp_red     = UART_Read();
            temp_green   = UART_Read();
            temp_blue    = UART_Read();

            for(unsigned char x=0; x< (led_number*3); x+=3)
            {
                a[x]   = temp_green;
                a[x+1] = temp_red;
                a[x+2] = temp_blue;
            }
            break;
        case 'e':// sending e will cause the leds to not update
                //  attempting to reduce flickering during color changes
            enable = !enable;
    }


    if(!enable)
        continue;
/*
        loop_count++;

        if(loop_count== 1024)
            loop_count =0;

        


        for(unsigned char x=0; x< (led_number*3); x+=3)
        {
            //a[x]=0;

            a[x]   = sine[(loop_count+(2*x))%1023 ];
            a[x+1] =sine[(loop_count+(2*x)+ 682)%1023];//(loop_ATcount + 682)>(1024) ? sine[(loop_count + 682)- 1024] : sine[loop_count + 682];
            a[x+2] =sine[(loop_count+(2*x)+ 341)%1023];//(loop_count + 341)>(1024) ? sine[(loop_count + 341)- 1024] : sine[loop_count + 341];


        }
*/




        #asm


        #endasm
        byte_count = (led_number*3);
        #asm

        
        BANKSEL PORTD  ;// select bank0

        //movlw 0b00100100     ;//    set up to read from linear data memory (page 52)
        movlw 0x20
        movwf FSR0H  ;//
        //movlw 0b00100000  ;// led array data starts at 0x2080-top of bank2
        movlw 0x50
        movwf FSR0L ;// setup file select register

        
                
        moviw fsr0++ ;// moves first byte into w and increments fsr0
        movwf _temp
        lslf _temp, f;

        
        byte_loop:
        // clock out bit 0
        bsf     PORTD, 0;
        btfss 3, 0; // if 1 then skip
        bcf     PORTD, 0;
        lslf _temp, f;
        nop
        bcf PORTD, 0;
        nop
        nop
        nop
        nop
        //----------------
        // clock out bit 1
        bsf     PORTD, 0;
        btfss 3, 0; // if 1 then skip
        bcf     PORTD, 0;
        lslf _temp, f;
        nop
        bcf PORTD, 0;
        nop
        nop
        nop
        nop
        //----------------
        // clock out bit 2
        bsf     PORTD, 0;
        btfss 3, 0; // if 1 then skip
        bcf     PORTD, 0;
        lslf _temp, f;
        nop
        bcf PORTD, 0;
        nop
        nop
        nop
        nop
        //----------------
        // clock out bit 3
        bsf     PORTD, 0;
        btfss 3, 0; // if 1 then skip
        bcf     PORTD, 0;
        lslf _temp, f;
        nop
        bcf PORTD, 0;
        nop
        nop
        nop
        nop
        //----------------
        // clock out bit 4
        bsf     PORTD, 0;
        btfss 3, 0; // if 1 then skip
        bcf     PORTD, 0;
        lslf _temp, f;
        nop
        bcf PORTD, 0;
        nop
        nop
        nop
        nop
        //----------------
        // clock out bit 5
        bsf     PORTD, 0;
        btfss 3, 0; // if 1 then skip
        bcf     PORTD, 0;
        lslf _temp, f;
        nop
        bcf PORTD, 0;
        nop
        nop
        nop
        nop
        //----------------

        // clock out bit 6
        bsf     PORTD, 0;
        btfss 3, 0; // if 1 then skip
        bcf     PORTD, 0;
        lslf _temp, f;
        nop
        bcf PORTD, 0;
        nop
        nop
        moviw fsr0++ ;// moves first byte into w and increments fsr0
        movwf _temp;
        //----------------
        // clock out bit 7
        bsf     PORTD, 0;
        btfss 3, 0; // if 1 then skip
        bcf     PORTD, 0;
                            ;// on the last bit setup the next byte
        lslf _temp, f;
        nop
        bcf PORTD, 0;
        nop
        //----------------
        decfsz _byte_count,f
        goto byte_loop



        #endasm


        //printf(" (%d,%d,%d),(%d) \n \n", a[0],a[1],a[2], sine[loop_count]);


        RD0 = 0;
        //__delay_ms(5);
/*
        PORTA= 1;
        __delay_ms(500);
        PORTA = 0;
        __delay_ms(500);
  
*/
    }





}