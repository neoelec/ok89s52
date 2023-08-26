;==========================================================================
;	   Exp18_6a.asm : Assembly Program for C & Assembly Link
;==========================================================================
;			 Designed and programmed by Duck-Yong Yoon in 2005.

Exp18_6	SEGMENT	CODE
	RSEG	Exp18_6

;------------------------------------------------
;	8-Bit Multiplication (R7 = R7 * R5)
;------------------------------------------------
	PUBLIC	_Mul_8bit

_Mul_8bit:
	PUSH	ACC
	PUSH	B
	MOV	A,R7			; R7 = multiplicand  (input)
	MOV	B,R5			; R5 = multiplier    (input)
	MUL	AB
	MOV	R7,A			; R7 = multiplication(output)
	POP	B
	POP	ACC
	RET

;------------------------------------------------
;	Delay for 1 Second(at 24MHz)
;------------------------------------------------
	PUBLIC	Delay_1sec

Delay_1sec:
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

	END

