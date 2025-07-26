/*
Writing one byte to an I2C slave
 */

#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//setup B0 for I2C
	UCB0CTLW0 |= UCSWRST;       // put in SW reset
	UCB0CTLW0 |= UCSSEL_3;      // choose SMCLK
	UCB0BRW = 10;               // set prescalar to 10


	UCB0CTLW0 |= UCMODE_3;      // put into I2C mode
	UCB0CTLW0 |= UCMST;         // set as master
	UCB0CTLW0 |= UCTR;          // Put into Tx mode (WRITE)
	UCB0I2CSA = 0x68;           // set slave address RTC=0x68

	UCB0CTLW1 |= UCASTP_2;      // auto STOP mode
	UCB0TBCNT = 1;              // Count = 1 byte

	// setup ports
	P1SEL1 &= ~BIT3;            // P1.3 = SCL
	P1SEL0 |= BIT3;

	P1SEL1 &= ~BIT2;            // P1.2 = SDA
	P1SEL0 |= BIT2;

	UCB0CTLW0 &= ~UCSWRST;       // take out of SW reset

	// enable B0 TX0 IRQ
	UCB0IE |= UCTXIE0;          // local enable for TX0
	__enable_interrupt();       // enable maskables

	int i;

	while(1)
	{
	    UCB0CTLW0 |= UCTXSTT;   // manually start message (START)
	    for(i=0; i<100; i=i+1){}// delay
	}

	return 0;
}

//ISRs
#pragma vector = EUSCI_B0_VECTOR
__interrupt void EUSCI_B0_I2C_ISR(void)
{
    UCB0TXBUF = 0xBB;
}
