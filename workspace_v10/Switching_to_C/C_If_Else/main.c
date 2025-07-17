#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	int i=0;
	int it_is_TWO = 0;          // 0 if not 2, 1 if 2

	while(1)
	{
	    for (i=0; i<5; i=i+1)
	    {
	        if (i==2)
	        {
	            it_is_TWO=1;
	        }
	        else
	        {
	            it_is_TWO = 0;
	        }

	    }

	}



	return 0;
}
