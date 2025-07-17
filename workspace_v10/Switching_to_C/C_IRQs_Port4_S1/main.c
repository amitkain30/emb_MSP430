#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// setup ports

	P1DIR |=BIT0;               // Config P1.0 to an output (LED1)
	P1OUT &= ~BIT0;             // Clear P1.0 initially (LED1)

	P4DIR &= ~BIT1;            // Config P4.1 as input (SW1)
	P4REN |= BIT1;              // Enable resistor
	P4OUT |= BIT1;              // Makes resistor a pull UP
	P4IES |= BIT1;              // Makes sensitivity H-to-L

	PM5CTL0 &=~LOCKLPM5;        // Turn on digital I/O

	//-- setup IRQ
	P4IE |= BIT1;              //Enable P4.1 IRQ
	__enable_interrupt();       // Enable Maskable IRQs
	P4IFG &=~BIT1;              // Clear P4.1 IRQ Flag

	while(1){}                  // Loop Forever

	return 0;
}


//-- ISRs---------------------//
#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_S1(void)
{
    P1OUT ^=BIT0;               // toggle LED1
    P4IFG &=~BIT1;            // Clear P4.1 IRQ Flag
}
