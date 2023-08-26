;------------------------------------------------------------------------------
;  This file is part of the C51 Compiler package
;  Copyright (c) 1988-2001 Keil Elektronik GmbH and Keil Software, Inc.
;------------------------------------------------------------------------------
;  STARTUP.A51:  This code is executed after processor reset.
;
;  To translate this file use A51 with the following invocation:
;
;     A51 STARTUP.A51
;
;  To link the modified STARTUP.OBJ file to your application use the following
;  BL51 invocation:
;
;     BL51 <your object file list>, STARTUP.OBJ <controls>
;
;------------------------------------------------------------------------------
;
;  User-defined Power-On Initialization of Memory
;
;  With the following EQU statements the initialization of memory
;  at processor reset can be defined:
;
IDATALEN	EQU	80H	; the length of IDATA memory in bytes.
;
;  Notes:  The IDATA space overlaps physically the DATA and BIT areas of the
;          8051 CPU. At minimum the memory space occupied from the C51 
;          run-time routines must be set to zero.
;------------------------------------------------------------------------------
;
;  The following EQU statements define the stack pointer for reentrant
;  functions and initialized it:
;
;  Stack Space for reentrant functions in the SMALL model.
;
IBPSTACK	EQU	0	; set to 1 if small reentrant is used.
IBPSTACKTOP	EQU	0FFH+1	; set top of stack to highest location+1.
;
;------------------------------------------------------------------------------

		NAME	?C_STARTUP

?C_C51STARTUP	SEGMENT   CODE
?STACK		SEGMENT   IDATA

		RSEG	?STACK
		DS	1

		EXTRN CODE (?C_START)
		PUBLIC	?C_STARTUP

		CSEG	AT	0
?C_STARTUP:	LJMP	STARTUP1

		RSEG	?C_C51STARTUP

STARTUP1:	MOV	R0,#IDATALEN - 1
		CLR	A
IDATALOOP:	MOV	@R0,A
		DJNZ	R0,IDATALOOP

EXTRN DATA (?C_IBP)
		MOV	?C_IBP,#LOW IBPSTACKTOP

		MOV	SP,#?STACK - 1

		MOV	30H,#00000101B		; LED data 1
		MOV	31H,#00001010B		; LED data 2

		LJMP	?C_START

		END
