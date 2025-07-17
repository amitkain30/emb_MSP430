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
			mov.w	#0, R14
			mov.w	#0, R15

while:
			cmp.w	#0, R14
			jz		case0
			cmp.w	#1, R14
			jz		case1
			cmp.w	#2, R14
			jz		case2
			cmp.w	#3, R14
			jz		case3
			jmp		default



case0:		mov.b	#1, R15
			jmp		end_switch

case1:		mov.w	#2, R15
			jmp		end_switch

case2:		mov.w	#4, R15
			jmp		end_switch

case3:		mov.w	#8, R15
			jmp		end_switch


default:	mov.w	#0, R15


end_switch:


end_while:
			jmp		while
                                            

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
            
