/*
 Writing a Register Addr + 3 Bytes to I2C Slave
 */

#include <msp430.h> 

char Packet[] = {0x03, 0x33, 0x44, 0x55};
int Data_Cnt = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// setting up B0 for I2C
	UCB0CTLW0 |= UCSWRST;       // put into SW Reset
	UCB0CTLW0 |= UCSSEL_3;      // choose SMCLK
	UCB0BRW = 10;               // set prescalar to 10

	UCB0CTLW0 |= UCMODE_3;      // put into I2C mode
	UCB0CTLW0 |= UCMST;         // put into Master mode
	UCB0CTLW0 |= UCTR;          // put into WRITE mode
	UCB0I2CSA = 0x68;            // set slave addr to 0x68

	UCB0CTLW1 |= UCASTP_2;      // auto stop mode
	UCB0TBCNT = sizeof(Packet); // # of bytes in packet

	// config ports
	P1SEL1 &= ~BIT3;            // P1.3 = SCL
	P1SEL0 |= BIT3;

	P1SEL1 &= ~BIT2;            // P1.2 = SDA
	P1SEL0 |= BIT2;

	PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

	UCB0CTLW0 &= ~UCSWRST;      // take out of SW reset

	// enable IRQs
	UCB0IE |= UCTXIE0;          // local enable for TX buf
	__enable_interrupt();       // enable maskables

	int i;
	while(1)
	{
	    UCB0CTLW0 |= UCTXSTT;   // Start message (START bit)
	    for(i=0; i<100; i=i+1){}// delay
	}

	return 0;
}

// ISRs
#pragma vector = EUSCI_B0_VECTOR
__interrupt void EUSCI_B0_I2C_ISR(void)
{
    if (Data_Cnt== (sizeof(Packet)-1))
    {
        UCB0TXBUF = Packet[Data_Cnt];
        Data_Cnt = 0;
    }
    else
    {
        UCB0TXBUF = Packet[Data_Cnt];
        Data_Cnt++;
    }

}
