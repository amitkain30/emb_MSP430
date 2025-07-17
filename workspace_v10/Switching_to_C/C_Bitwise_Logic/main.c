#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer


	int e = 0b1111111111111110;
	int f = 0x0001;

	while(1)
	{
	    e = ~e;                 // invert all bits in e
	    e = e | BIT7;           // set bit 7 in e
	    e = e &  ~ BIT0;        // clear bit 0 in e
	    e = e ^ BIT4;           // toggle bit 4
	    e |= BIT6;              // set bit 6
	    e &= ~BIT1;             // clear bit 1
	    e ^= BIT3;              // toggle bit 3

	    f = f << 1;
	    f = f << 2;
	    f = f >> 1;
	}

	
	return 0;
}
