#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer


    //-- setup UART
    UCA1CTLW0 |= UCSWRST;       // put UART A1 into SW reset

    UCA1CTLW0 |= UCSSEL__SMCLK; // choose SMCLK for UART A1 (115200 baud)
    UCA1BRW = 8;                // set prescalar to 8
    UCA1MCTLW |= 0xD600;        // configure modulation settings + low freq

    P4SEL1 &= ~BIT3;            // P4SEL1.3:P4SEL0.3=01
    P4SEL0 |= BIT3;             // puts UART A1 Tx on P4.3

    PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

    UCA1CTLW0 &= ~UCSWRST;      // put UART A1 into SW reset

    int position;
    int i,j ;

    char message[] = "Hello World ";

    while(1)
    {
        for (position=0; position<sizeof(message); position++)
        {
            UCA1TXBUF = message[position];
            for (i=0; i<100; i++)
            {
                // delay between characters
            }
        }

        for (j=0; j<30000; j=j+1)
        {
                //delay between strings
        }
    }


	
	return 0;
}
