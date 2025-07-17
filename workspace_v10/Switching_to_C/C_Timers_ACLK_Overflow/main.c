#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	//setup ports
	P1DIR |= BIT0;              // set P1.0 to an output LED1
	P1OUT &= ~BIT0;             // clear LED1 initially
	PM5CTL0 &= ~LOCKLPM5;       // turn on GPIO

	//setup timer
	TB0CTL |= TBCLR;            // reset timer
	TB0CTL |= TBSSEL__ACLK;     // Clock = ACLK
	TB0CTL |= MC__CONTINUOUS;   // Mode = Continuous

	//setup TB0 overflow IRQ
	TB0CTL |= TBIE;             // local enable for TB0 Overflow
	__enable_interrupt();       // Enable maskable IRQs
	TB0CTL &= ~TBIFG;           // Clear IRQ Flag

	//main loop
	while(1){}


	
	return 0;
}

//ISRs-----------------//
#pragma vector = TIMER0_B1_VECTOR
__interrupt void IRS_TB0_Overflow(void)
{
    P1OUT ^= BIT0;              // toggle LED1
    TB0CTL &= ~TBIFG;            // Clear IRQ Flag
}
