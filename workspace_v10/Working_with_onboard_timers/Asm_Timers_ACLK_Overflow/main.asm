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
;---setup LED
			bis.b	#BIT0, &P1DIR			; set p1.0 to output
			bic.b	#BIT0, &P1OUT			; turn LED1 off
			bic.b	#LOCKLPM5, &PM5CTL0		; enable digital I/O


;---setup Timer B0
			bis.w	#TBCLR, &TB0CTL			; clear TB0
			bis.w	#TBSSEL__ACLK, &TB0CTL	; choose ACLK
			bis.w	#MC__CONTINUOUS, &TB0CTL	; put into continuous mode


;-setup overflow IRQ
			bis.w	#TBIE, &TB0CTL			; local enable for TB0 overflow
			eint							; enable global for maskables
			bic.w	#TBIFG, &TB0CTL			; clear flag for first use

main:
			jmp		main

;-------------------------------------------------------------------------------
; Interrupt Service Routines
;-------------------------------------------------------------------------------
ISR_TB0_Overflow:
			xor.b	#BIT0, &P1OUT			; toggle LED1
			bic.w	#TBIFG, &TB0CTL			; clear flag for first use
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
            
            .sect	".int42"				; init vector table for TB0 overflow
            .short	ISR_TB0_Overflow
