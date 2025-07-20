#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- setup UART A1
	UCA1CTLW0 |= UCSWRST;       // put A1 into SW reset

	UCA1CTLW0 |= UCSSEL__SMCLK; // BRCLK=SMCLK (want 115200 baud)
	UCA1BRW = 8;                // Prescalar = 8
	UCA1MCTLW = 0xD600;         // set modulation & low-freq

	//-- setup ports
	P4SEL1 &= ~BIT2;            // P4.2 set function to UART A1 Rx (01)
	P4SEL0 |= BIT2;

	P1DIR |= BIT0;              // set P1.0 to output (LED1)
	P1OUT &= ~BIT0;             // turn off LED1 initially

	PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

	UCA1CTLW0 &= ~UCSWRST;      // take UART A1 out of SW reset

	//-- Setup IRQ A1 RXIFG
	UCA1IE |= UCRXIE;           // local enable for A1 RXIFG
	__enable_interrupt();         // global enable for maskables (GIE bit in SR)

	// main loop
	while(1){}                  // do nothing

	return 0;
}

//ISRs
#pragma vector = EUSCI_A1_VECTOR
__interrupt void EUSCI_A1_RX_ISR(void)
{
    if (UCA1RXBUF == 't')
    {
        P1OUT ^= BIT0;          // toggle LED1
    }
}
