#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	//-- Setup SPI A0
	UCA0CTLW0 |= UCSWRST;       // put A0 into SW reset

	UCA0CTLW0 |= UCSSEL__SMCLK; // choose SMCLK
	UCA0BRW = 10;               // set prescalar to 10 to get SCLK = 1M/10=100kHz

	UCA0CTLW0 |= UCSYNC;        // put A0 into SPI mode
	UCA0CTLW0 |= UCMST;         // put into SPI master

	//--configure the ports
	P1SEL1 &= ~BIT5;            // P1.5 use SCLK (01)
	P1SEL0 |= BIT5;             //

	P1SEL1 &= ~BIT7;            // P1.7 use SIMO
	P1SEL0 |= BIT7;

	P1SEL1 &= ~BIT6;            // P1.6 use SOMI
	P1SEL0 |= BIT6;

	PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

	UCA0CTLW0 &= ~UCSWRST;      // take A0 out of SW reset

	int i;

	while (1)
	{
	    UCA0TXBUF = 0X4D;       // send x4D out over SPI
	    for (i=0; i<10000; i=i+1){}
	}


	return 0;
}
