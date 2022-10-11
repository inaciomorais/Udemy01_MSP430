#include <msp430.h> 

void init_pins(void);
void setup_timer0(void);
void setup_timer1(void);
unsigned char button_pushed(void);

main()
{
    BCSCTL1 = CALBC1_1MHZ;      // 1MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL = CALDCO_1MHZ;       // BCSCTL1 register settings)
    BCSCTL2 = DIVS_3;           // Basic Clock System Control Register 2
                                // DIVS_3 = SMCLK Divider 3: /8
                                // 1 s / ( 1000000 MHz [DCOCLK] / 8 [BCSCTL2 DIVSx: SMCLK Divider] / 8 [TACTL IDx: Timer A input divider] )
                                // = 0.000064 s = 64 us

    setup_timer0();

    setup_timer1();

    init_pins();

    _BIS_SR(GIE);

    while(1) {
        while(button_pushed()){
            P1OUT = BIT6;
        }

        P1OUT = P1OUT & 0xBF;
    }
}

#pragma vector=TIMER0_A0_VECTOR

__interrupt void Timer0_ISR (void)
{
    P1OUT = P1OUT ^ BIT0;
}

#pragma vector=TIMER1_A0_VECTOR

__interrupt void Timer1_ISR (void)
{
    WDTCTL = WDTPW | WDTCNTCL;
}

void setup_timer0(void) {
    TA0CCR0 = 15625; //~ 1s

    TA0CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0
    TA0CCTL0 = CCIE;
}

void setup_timer1(void) {
    TA1CCR0 = 156; //~ 0,01s

    TA1CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0
    TA1CCTL0 = CCIE;
}

void init_pins(void) {
    P1DIR = BIT0 | BIT6;

    P1OUT = BIT3;
    P1REN = BIT3;
}

unsigned char button_pushed(void) {
    return !(BIT3 & P1IN);
}
