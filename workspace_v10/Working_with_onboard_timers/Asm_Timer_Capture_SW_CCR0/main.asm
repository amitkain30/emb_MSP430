;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
; setup Ports
			bis.b	#BIT0, &P1DIR			; set P1.0 to output (LED1)
			bic.b	#BIT0, &P1OUT			; LED1 = off initially

			bic.b	#BIT1, &P4DIR			; set P4.1 to input (SW1)
			bis.b	#BIT1, &P4REN			; enable resistor
			bis.b	#BIT1, &P4OUT			; set to pull up
			bis.b	#BIT1, &P4IES			; irq set to HIGH to LOW

			bis.b	#LOCKLPM5, &PM5CTL0		; turn on digital IO

; setup the IRQ SW1
			bis.b	#BIT1, &P4IE			; local enable for SW1
			eint							; enable global for maskables
			bic.b	#BIT1, &P4IFG			; clear flag

; setup timer
			bis.w	#TBCLR, &TB0CTL			; clear timer
			bis.w	#TBSSEL__ACLK, &TB0CTL	; choose ACLK
			bis.w	#ID__8, &TB0CTL			; div-by-4 in 1st stage
			bis.w	#MC__CONTINUOUS, &TB0CTL	; cont... mode

; setup capture
			bis.w	#CAP, &TB0CCTL0			; puts in capture mode
			bis.w	#CM__BOTH, &TB0CCTL0	; both edge sens.
			bis.w	#CCIS__GND, &TB0CCTL0	; input signal = GND

; init R4
			mov.w	#0, R4

main:
			jmp		main

;-------------------------------------------------------------------------------
; ISR
;-------------------------------------------------------------------------------

ISR_S1:
			xor.b	#BIT0, P1OUT			; toggle LED
			xor.w	#CCIS0, &TB0CCTL0		; cause capture
			mov.w	&TB0CCR0, R4			; store off value
			bic.b	#BIT1, &P4IFG			; clear flag
			reti


;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
            .sect	".int22"				; P4 vector
            .short	ISR_S1
