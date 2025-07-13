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
;setup LEDs
			bis.b	#BIT0, &P1DIR			; set p1.0 to output (LED1)
			bis.b	#BIT6, &P6DIR			; set p6.6 to output (LED2)
			bic.b	#BIT0, &P1OUT			; clear LED1
			bic.b	#BIT6, &P6OUT			; set LED2

;setup timer B0
			bis.w	#TBCLR, &TB0CTL			; clear timer B0
			bis.w	#TBSSEL__SMCLK, &TB0CTL	; choose SMCLk
			bis.w	#ID__4, &TB0CTL			; div4 in first divider stage
			bis.w	#MC__CONTINUOUS, &TB0CTL	; put timer into continuous mode

; setup IRQ
			bis.w	#TBIE, &TB0CTL			; local enable for overflow
			eint							; global enable
			bic.w	#TBIFG, &TB0CTL			; clear flag

main:
			jmp		main


;-------------------------------------------------------------------------------
; Interrupt Service Routines
;-------------------------------------------------------------------------------
ISR_TB0_Overflow:
			xor.b	#BIT0, &P1OUT			; toggle LED1
			xor.b	#BIT6, &P6OUT			; toggle LED2
			bic.w	#TBIFG, &TB0CTL			; clear flag
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
            
            .sect	".int42"				; Timer B0 Overflow Vector
            .short	ISR_TB0_Overflow
