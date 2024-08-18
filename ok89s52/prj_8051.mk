PRJ_SDCC_MK_FILE	:= $(realpath $(lastword $(MAKEFILE_LIST)))
PRJ_SDCC_MK_DIR		:= $(shell dirname $(PRJ_SDCC_MK_FILE))

MK_RACCOON_DIR		:= $(HOME)/iHDD00/08.PROJECT/mk-raccoon

PROGMEM			?= paulmon

MCU			:= mcs51
ASMCU			:= 8051
F_CPU			:= 24000000

OK89S52CLIB		:= $(PRJ_SDCC_MK_DIR)/libs
EXTRAINCDIRS		+= $(OK89S52CLIB)
VPATH			+= $(OK89S52CLIB)

ifeq ($(PROGMEM),paulmon)
ASRCS			+= PAULMON.asm
EXTRAINCDIRS		+= $(OK89S52CLIB)/w_PAULMON
XRAM_LOC		:= --xram-loc 0x4000
CODE_LOC		:= --code-loc 0x2000
else
EXTRAINCDIRS		+= $(OK89S52CLIB)/wo_PAULMON
XRAM_LOC		:= --xram-loc 0x2000
CODE_LOC		:= --code-loc 0x0000
endif

include $(MK_RACCOON_DIR)/mk/base_sdcc.mk
include $(MK_RACCOON_DIR)/dbg/paulmon.mk
