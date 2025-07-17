#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	int count = 0;

	while(1)
	{
	    count = count +1;

	}


	return 0;
}
