OK89S52C_MK_FILE	:= $(realpath $(lastword $(MAKEFILE_LIST)))
OK89S52C_PATH		:= $(shell dirname $(OK89S52C_MK_FILE))

MCU			:= mcs51
ASMCU			:= 8051
F_CPU			:= 24000000

OK89S52CLIB		:= $(OK89S52C_PATH)/libs
EXTRAINCDIRS		+= $(OK89S52CLIB)
VPATH			+= $(OK89S52CLIB)

USE_PAULMON		:= y

ifeq ($(USE_PAULMON),y)
ASRCS			+= PAULMON.asm
EXTRAINCDIRS		+= $(OK89S52CLIB)/w_PAULMON
XRAM_LOC		:= --xram-loc 0x4000
CODE_LOC		:= --code-loc 0x2000
else
EXTRAINCDIRS		+= $(OK89S52CLIB)/wo_PAULMON
endif

include $(OK89S52C_PATH)/../sdcc.mk
include $(OK89S52C_PATH)/../paulmon.mk
