#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	int i = 0;
	int count = 0;

	while(1)
	{
        for (i=0; i<10; i=i+1)
        {
            count = i;
        }
	}

	return 0;
}
