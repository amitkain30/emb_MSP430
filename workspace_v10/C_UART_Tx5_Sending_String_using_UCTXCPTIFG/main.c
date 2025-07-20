#include <msp430.h> 


char message[] = "Hello World ";
unsigned int position;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- setup UART
    UCA1CTLW0 |= UCSWRST;       // put UART A1 into SW reset

    UCA1CTLW0 |= UCSSEL__SMCLK; // choose SMCLK for UART A1 (115200 baud)
    UCA1BRW = 8;                // set prescalar to 8
    UCA1MCTLW |= 0xD600;        // configure modulation settings + low freq

    //--configure ports
    P4DIR &= ~BIT1;             // Make P4.1 an input (SW1)
    P4REN |= BIT1;              // Enables resistor
    P4OUT |= BIT1;              // make it a pull up resistor
    P4IES |= BIT1;              // Make IRQ sense High-to-Low

    P4SEL1 &= ~BIT3;            // Sets P4.5 to use UART A1 Tx function
    P4SEL0 |= BIT3;

    PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

    UCA1CTLW0 &= ~UCSWRST;      // put UART A1 into SW reset

    // Enable IRQs
    P4IE |= BIT1;               // enables SW1 IRQ
    P4IFG &= ~BIT1;             // clears flag
    __enable_interrupt();       // global en IRQs

    while(1)
    {

    }

	return 0;
}

//----ISRs------
#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_S1(void)
{
    position = 0;
    UCA1IE |= UCTXCPTIE;        // turns on Tx complete IRQ
    UCA1IFG &= ~UCTXCPTIFG;     // clears Tx complete flag
    UCA1TXBUF = message[position];   // put first character from message into Tx buf

    P4IFG &= ~BIT1;             // clear flag for P4.1
}



#pragma vector = EUSCI_A1_VECTOR
__interrupt void ISR_EUSCI_A1(void)
{
    if (position == sizeof(message))
    {
        UCA1IE &= ~UCTXCPTIE;    // Turn off Tx complete IRQ
    }
    else
    {
        position++;
        UCA1TXBUF = message[position];  //put next char into Tx buf
    }

    UCA1IFG &= ~UCTXCPTIFG;       // clear Tx complete flag
}
