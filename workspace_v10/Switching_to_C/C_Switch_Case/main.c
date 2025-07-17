#include <msp430.h> 



int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	int i = 0;

	int it_is_ONE = 0;          //assert when i=1
	int it_is_TWO = 0;          //assert when i=2

	while (1)
	{
	    for (i=0; i<5; i=i+1)
	    {
	        switch(i)
	        {
	        case 1: it_is_ONE = 1;
	                it_is_TWO = 0;
	                break;
	        case 2: it_is_ONE = 0;
	                it_is_TWO = 1;
	                break;
	        default:it_is_ONE = 0;
	                it_is_TWO = 0;
	                break;

	        }
	    }
	}




	return 0;
}
