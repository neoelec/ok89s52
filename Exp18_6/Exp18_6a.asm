;==========================================================================
;          Exp18_6a.asm : Assembly Program for C & Assembly Link
;==========================================================================
;                        Designed and programmed by Duck-Yong Yoon in 2005.

;------------------------------------------------
;	8-Bit Multiplication (dpl = dpl * _Mul_8bit_PARM_2)
;------------------------------------------------
        .globl _Mul_8bit
        .globl _Mul_8bit_PARM_2
        .area OSEG
_Mul_8bit_PARM_2:
        .ds     1
        .area CSEG
_Mul_8bit:
        PUSH    A
        PUSH    B
        MOV     A, DPL                 ; DPL = multiplicand (input)
        MOV     B, _Mul_8bit_PARM_2    ; _Mul_8bit_PARM_2 = multiplier (input)
        MUL     AB
        MOV     DPL, a                 ; DPL = multiplication(output)
        POP     B
        POP     A
        RET

;------------------------------------------------
;       Delay for 1 Second(at 24MHz)
;------------------------------------------------
        .globl _Delay_1sec
        .area CSEG
_Delay_1sec:
        PUSH	ACC
        PUSH	B

        MOV	A,#200			; 200*250*40 = 2000000 cycle
DELAY1:	MOV	B,#250
DELAY2:	PUSH	B			; 2
        PUSH	B			; 2
        PUSH	B			; 2
        PUSH	B			; 2
        PUSH	B			; 2
        PUSH	B			; 2
        PUSH	B			; 2
        PUSH	B			; 2
        PUSH	B			; 2
        NOP				; 1
        NOP				; 1
        POP	B			; 2
        POP	B			; 2
        POP	B			; 2
        POP	B			; 2
        POP	B			; 2
        POP	B			; 2
        POP	B			; 2
        POP	B			; 2
        POP	B			; 2
        DJNZ	B,DELAY2		; 2
        DJNZ	ACC,DELAY1

        POP	B
        POP	ACC
        RET
