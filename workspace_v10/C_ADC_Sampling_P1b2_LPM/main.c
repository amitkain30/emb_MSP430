/*
 Reading Voltage with Conversion Complete IRQ & LPM
 */

#include <msp430.h> 

unsigned int ADC_Value;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // setup ports
    P1DIR |= BIT0;              // Config P1.0 as output (LED1)
    P6DIR |= BIT6;              // Config P6.6 as output (LED2)

    P1SEL1 |= BIT2;             // Configure P1.2 as analog function
    P1SEL0 |= BIT2;             // 11

    PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

    // Configure ADC
    ADCCTL0 &= ~ADCSHT;         // conversion cycles = 16
    ADCCTL0 |= ADCSHT_2;        // ADCSHT = 10
    ADCCTL0 |= ADCON;           // turn on ADC

    ADCCTL1 |= ADCSSEL_2;       // Selects SMCLK (1MHz)
    ADCCTL1 |= ADCSHP;          // use ADC timer to trigger conversion

    ADCCTL2 &= ~ADCRES;         // set resolution to 12-bit
    ADCCTL2 |= ADCRES_2;        // 10

    ADCCTL0 |= ADCINCH_2;       // Select A2

    // Setup IRQ
    ADCIE |= ADCIE0;            // conversion complete IRQ, local enable


    while(1)
    {
        ADCCTL0 |= ADCENC | ADCSC;  // enable conversion
        __bis_SR_register(GIE|LPM0_bits);   // enabled maskables
                                            // put into LPM0

    }

    return 0;
}


// ISR
#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void)
{
    __bic_SR_register_on_exit(LPM0_bits);
    ADC_Value = ADCMEM0;        // Read ADC Value

    if (ADC_Value>3613)
    {
        P1OUT |= BIT0;          // Turn on LED1
        P6OUT &= ~BIT6;         // Turn OFF LED2
    }
    else
    {
        P1OUT &= ~BIT0;         // Turn OFF LED1
        P6OUT |= BIT6;          // Turn ON LED2
    }
}

