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
init:
; setup LED
			bis.b	#BIT0, &P1DIR			; set p1.0 to make output (LED1)
			bis.b	#BIT0, &P1OUT			; set LED1 initially
			bic.b	#LOCKLPM5, &PM5CTL0		; turn on digital I/O

; setup timer B0
			bis.w	#TBCLR, &TB0CTL			; clears timer B0
			bis.w	#TBSSEL__ACLK, &TB0CTL	; choose ACLK as source
			bis.w	#MC__UP, &TB0CTL		; put in UP mode

; setup compares
			mov.w	#32768, &TB0CCR0		; CCR0 = 32,768
			mov.w	#1638, &TB0CCR1			; CCR1 = 1,638

; setup IRQs
			bis.w	#CCIE, &TB0CCTL0		; local IRQ enable for CCR0
			bic.w	#CCIFG, &TB0CCTL0		; clear CCR0 Flag

			bis.w	#CCIE, &TB0CCTL1		; local IRQ enable for CCR1
			bic.w	#CCIFG, &TB0CCTL1		; clear CCR1 Flag

			eint							; global enable

main:
			jmp		main

;-------------------------------------------------------------------------------
; ISRs
;-------------------------------------------------------------------------------

ISR_TB0_CCR1:
			bic.b	#BIT0, &P1OUT			; LED1=0
			bic.w	#CCIFG, &TB0CCTL1		;clear CCR1 flag
			reti

ISR_TB0_CCR0:
			bis.b	#BIT0, &P1OUT			; LED1=1
			bic.w	#CCIFG, &TB0CCTL0		; clear CCR1 Flag
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
            
            .sect	".int43"				; CCR0 Vector
            .short	ISR_TB0_CCR0

            .sect	".int42"				; CCR1 Vector
            .short	ISR_TB0_CCR1
