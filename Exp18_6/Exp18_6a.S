;==========================================================================
;           Exp18_6a.S : Assembly Program for C & Assembly Link
;==========================================================================
;                       Designed and programmed by Duck-Yong Yoon in 2005.

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
        push    a
        push    b
        mov     a, dpl                  ; dpl = multiplicand (input)
        mov     b, _Mul_8bit_PARM_2     ; _Mul_8bit_PARM_2 = multiplier (input)
        mul     ab
        mov     dpl, a                  ; dpl = multiplication(output)
        pop     b
        pop     a
        ret

;------------------------------------------------
;       Delay for 1 Second(at 22.1184MHz)
;------------------------------------------------
        .globl _Delay_1sec
        .area CSEG
_Delay_1sec:
        push	acc
        push	b

        mov	a, #200                 ; 200*230*40 = 1840000 cycle
delay1:	mov	b, #230
delay2:	push	b                       ; 2
        push	b                       ; 2
        push	b                       ; 2
        push	b                       ; 2
        push	b                       ; 2
        push	b                       ; 2
        push	b                       ; 2
        push	b                       ; 2
        push	b                       ; 2
        nop                             ; 1
        nop                             ; 1
        pop	b                       ; 2
        pop	b                       ; 2
        pop	b                       ; 2
        pop	b                       ; 2
        pop	b                       ; 2
        pop	b                       ; 2
        pop	b                       ; 2
        pop	b                       ; 2
        pop	b                       ; 2
        djnz	b, delay2               ; 2
        djnz	acc, delay1

        pop	b
        pop	acc
        ret
