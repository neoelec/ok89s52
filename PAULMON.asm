;------------------------------------------------
;	Reserve for the Single Step Function
;------------------------------------------------

.include /BASE_ADDR.inc/

		.area	CODE	(ABS,CODE)
		.org	BASE+0x0013	; External 1
	RETI
		.ds	7

		.area	ABS.PAULMON	(ABS)
		.org	0x007C
		.ds	2
