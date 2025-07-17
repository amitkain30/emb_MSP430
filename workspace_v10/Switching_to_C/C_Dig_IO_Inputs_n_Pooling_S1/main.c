#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Setup Ports
	P1DIR |=BIT0;               //Set P1.0 to an output (LED1)
	P1OUT &= ~BIT0;             // Clear LED1

	P4DIR &= ~BIT1;             // Set P4.1 to an input (SW1)
	P4REN |= BIT1;              // Enables resistor
	P4OUT |= BIT1;              // Sets resistor to pull UP

	PM5CTL0 &= ~LOCKLPM5;       // Turn on Digital IO


	int i;
	int SW1;

	while(1)
	{
	    SW1 = P4IN;             // Read Port 4
	    SW1 &=BIT1;             // Clear all bits except SW1

	    if (SW1==0)
	    {
	        P1OUT ^=BIT0;       // Turn on LED1

	    }


	    for (i=0; i<10000; i++)
	    {
	        // do nothing
	    }

	}

	return 0;
}
