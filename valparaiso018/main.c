#include <msp430.h> 

//#define GREEN_LED 0x40        // P1.6 is the GREEN LED
//#define CLEAR_GREEN_LED 0xBF  // Used to turn off the GREEN LED
#define RED_LED 0x01        // P1.0 is the RED LED
#define CLEAR_RED_LED 0xFE  // Used to turn off the RED LED
#define BUTTON13 0x08       // P1.3 is the button

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer ('DEVELOPMENT')

    P1DIR = RED_LED;

    P1OUT = BUTTON13;
    P1REN = BUTTON13;

    while(1)
    {
        while((BUTTON13 & P1IN) == 0){
            P1OUT = P1OUT | RED_LED;
        }
        P1OUT = P1OUT & CLEAR_RED_LED;
    }
}
