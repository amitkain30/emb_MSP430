/*
ADC: Reading voltage with conversion-complete polling
 */

#include <msp430.h> 

unsigned int ADC_Value;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//setup ports
	P1DIR |= BIT0;              // set P1.0 to output (LED1)
	P6DIR |= BIT6;              // set P6.6 to output (LED2)

	P1SEL1 |= BIT2;             // choose Analog function for P1.2
	P1SEL0 |= BIT2;             // 11 = Analog

	PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

	// Configure ADC
	ADCCTL0 &= ~ADCSHT;         // set conv clock cycles = 16 (10)
	ADCCTL0 |= ADCSHT_2;
	ADCCTL0 |= ADCON;           // turn on ADC

	ADCCTL1 |= ADCSSEL_2;       // chooses SMCLK
	ADCCTL1 |= ADCSHP;          // sample signal source = sampling timer

	ADCCTL2 &= ~ADCRES;         // clear resolution
	ADCCTL2 |= ADCRES_2;        // 12-bit resolution

	ADCMCTL0 |= ADCINCH_2;      // ADC input = A2 (P1.2)

	while(1)
	{
	    ADCCTL0 |= ADCENC | ADCSC;  // Enable and Start Conv.

	    while ((ADCIFG & ADCIFG0)==0);

	    ADC_Value = ADCMEM0;

	    if (ADC_Value>3613)
	    {
	        P1OUT |= BIT0;      // LED1 = ON (red)
	        P6OUT &= ~BIT6;     // LED2 = OFF (green)
	    }
	    else
	    {
	        P1OUT &= ~BIT0;     // LED1 = OFF (red)
            P6OUT |= BIT6;      // LED2 = ON (green)
	    }
	}

	return 0;
}
