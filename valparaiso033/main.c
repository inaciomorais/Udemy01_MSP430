#include <msp430.h> 

#define RED_LED 0x01        // P1.0 is the RED LED

main()
{
    unsigned char interval = 0;

    BCSCTL1 = CALBC1_1MHZ;      // 1MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL = CALDCO_1MHZ;       // BCSCTL1 register settings)
    BCSCTL2 = DIVS_3;           // Basic Clock System Control Register 2
                                // DIVS_3 = SMCLK Divider 3: /8
                                // 1 s / ( 1000000 MHz [DCOCLK] / 8 [BCSCTL2 DIVSx: SMCLK Divider] / 8 [TACTL IDx: Timer A input divider] )
                                // = 0,000064 s = 64 us

    TACCR0 = 156;

    TA0CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0

    P1DIR = RED_LED;

    while(1)
    {
        if(TACTL & TAIFG) {
            interval++;
            TACTL = TACTL & (~TAIFG);
            WDTCTL = WDTPW | WDTCNTCL;

            if (interval == 100) {
                interval = 0;
                P1OUT = P1OUT ^ RED_LED;
            }
        }
    }
}
