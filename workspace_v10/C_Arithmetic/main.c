#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	int a = 2;
	int b = 3;
	int c = 4;
	int d = 5;

	while(1)
	{
	    b = a + b;              //add.w
	    d = c - d;

	    b = b+1;
	    b++;

	    d = d-1;
	    d--;



	}

	return 0;
}
