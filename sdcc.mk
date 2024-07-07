SDCC_MK_FILE		:= $(realpath $(lastword $(MAKEFILE_LIST)))
SDCC_PATH		:= $(shell dirname $(SDCC_MK_FILE))

# MCU name.
#   mcs51   : the Intel MCS51 family of processors
#   ds390   : the Dallas DS80C390 processor
#   ds400   : the Dallas DS80C400 processor
#   hc08    : the Freescale/Motorola HC08 (aka 68HC08) family of processors
#   s08     : the Freescale/Motorola S08 (aka 68HCS08, HCS08, CS08) family of processors
#   z80     : the Zilog Z80 family of processors
#   z180    : the Zilog Z180 family of processors
#   r2k     : the Rabbit 2000 / Rabbit 3000 family of processors
#   r3ka    : the Rabbit 3000A family of processors
#   sm83    : the Sharp SM83 processor
#   tlcs90  : the Toshiba TLCS-90 processor
#   ez80_z80: the Zilog eZ80 processor in Z80 mode
#   stm8    : the STMicroelectronics STM8 family of processors
#   pdk13   : Padauk processors with 13 bit wide program memory
#   pdk14   : Padauk processors with 14 bit wide program memory
#   pdk15   : Padauk processors with 15 bit wide program memory
#   pic14   : the Microchip PIC 14-bit processors (p16f84 and variants. In development, not complete)
#   pic16   : the Microchip PIC 16-bit processors (p18f452 and variants. In development, not complete)
#   mos6502 : the original MOS Technology NMOS 6502 processor and compatible derivatives 
#   mos65c02: the CMOS Rockwell/WDC 65C02
MCU			?= mcs51

# Processor frequency.
F_CPU			?= 24000000

# The start location of the external ram, default value is 0.
XRAM_LOC		?=

# The start location of the code segment, default value is 0.
CODE_LOC		?=

# Target file name
TARGET			?=

# Output directories
BINDIR			?= bin
OBJDIR			?= obj

# Define output file
OUTPUT			?= $(addprefix $(BINDIR)/, $(TARGET))

# Optimization options here.
#   code-speed
#   code-size
OPT			?= code-size

# Compiler flag to set the C Standard level.
#   c89    : ISO C90 (aka ANSI C89) standard
#   c95    : ISO C95 (aka ISO C94) standard
#   c99    : ISO C99 standard
#   c11    : ISO C11 standard
#   c17    : ISO C17 standard
#   c23    : ISO C23 standard
#   sdcc89 : ISO C90 (aka ANSI C89) standard with SDCC extensions
#   sdcc99 : ISO C99 standard with SDCC extensions
#   sdcc11 : ISO C11 standard with SDCC extensions (default)
#   sdcc11 : ISO C17 standard with SDCC extensions
#   sdcc23 : ISO C23 standard with SDCC extensions
CSTANDARD		?= sdcc11

# Assembler MCU name.
ASMCU_mcs51		:= 8051
ASMCU_ds390		:= 390
ASMCU_ds400		:= 390
ASMCU_hc08		:= 6808
ASMCU_s08		:= 6808
ASMCU_z80		:= z80
ASMCU_z180		:= z80
ASMCU_r2k		:= rab
ASMCU_r3ka		:= rab
ASMCU_sm83		:= gb
ASMCU_tlcs90		:= tlcs90
ASMCU_ez80_z80		:= z80
ASMCU_stm8		:= stm8
ASMCU_pdk13		:= pdk13
ASMCU_pdk14		:= pdk14
ASMCU_pdk15		:= pdk15
ASMCU_pic14		:=
ASMCU_pic16		:=
ASMCU_mos6502		:= 6500

# VPATH variable
VPATH			+=

# Define all C sorce files.
CSRCS			+=

# Define all Assembler source files.
ASRCS			+=

# List any extra directories to look for include files here.
EXTRAINCDIRS		+=

# Place -I options here
CINCS			+=

# Place -D or -U options here
CDEFS			+= -DF_CPU=$(F_CPU)UL

# Compiler Options
CFLAGS			+= $(CDEFS) -m$(MCU) --opt-$(OPT) --std-$(CSTANDARD)
CFLAGS			+= --debug
CFLAGS			+= $(CINCS)
CFLAGS			+= $(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS			+= --verbose

# Assembler Options
ASFLAGS			+= -x -l -s
ASFLAGS			+= -j -y
ASFLAGS			+= $(patsubst %,-I%,$(EXTRAINCDIRS))

# Linker Options
LDFLAGS			+= --out-fmt-ihx --opt-$(OPT)
LDFLAGS			+= --debug
LDFLAGS			+= $(XRAM_LOC)
LDFLAGS			+= $(CODE_LOC)
LDFLAGS			+= --verbose

# Define programs and commands.
CC			:= sdcc
AS			:= sdas$(ASMCU_$(MCU))
REMOVE			:= rm -rf
COPY			:= cp

# Define all object files.
COBJS			:= $(addprefix $(OBJDIR)/, $(CSRCS:.c=.rel))
AOBJS			:= $(addprefix $(OBJDIR)/, $(ASRCS:.asm=.rel))

# Define Messages
MSG_SIZE_BEFORE		:= Size before:
MSG_SIZE_AFTER		:= Size after:
MSG_FLASH		:= Creating load file for Flash:
MSG_LINKING		:= Linking:
MSG_COMPILING		:= Compiling:
MSG_ASSEMBLING		:= Assembling:
MSG_CLEANING		:= Cleaning project:

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS		:= $(CFLAGS)
ALL_ASFLAGS		:= $(ASFLAGS)

all: build

build: sdccversion sizebefore $(BINDIR) $(OBJDIR) output sizeafter

output: hex

hex: $(OUTPUT).hex $(OUTPUT).bin

sdccversion:
	$(CC) --version

$(BINDIR) $(OBJDIR):
	@mkdir -p $@

# Display size of file.
sizebefore: | sdccversion
	@if [ -f $(OUTPUT).mem ]; then \
		echo; \
		echo $(MSG_SIZE_BEFORE); \
		cat $(OUTPUT).mem; \
		echo; \
	fi

sizeafter: | output
	@if [ -f $(OUTPUT).mem ]; then \
		echo; \
		echo $(MSG_SIZE_AFTER); \
		cat $(OUTPUT).mem; \
		echo; \
	fi

%.bin: %.ihx
	@echo
	@echo $(MSG_FLASH) "Binary"
	srec_cat $< -Intel -o $@ -Binary

%.hex: %.ihx
	@echo
	@echo $(MSG_FLASH) "Intel"
	srec_cat $< -Intel -o $@ -Intel

$(OUTPUT).ihx: $(COBJS) $(AOBJS) | $(BINDIR)
	@echo
	@echo $(MSG_LINKING)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile: create object files from C source files.
$(COBJS): $(OBJDIR)/%.rel: %.c | $(OBJDIR)
	@echo
	@echo $(MSG_COMPILING)
	$(CC) -c $(ALL_CFLAGS) -o $@ $<

# Assemble: create object files from assembler source files
$(AOBJS): $(OBJDIR)/%.rel: %.asm | $(OBJDIR)
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(AS) $(ALL_ASFLAGS) -o $@ $<

# Target: clean project.
clean: clean_list

clean_list:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(BINDIR)
	$(REMOVE) $(OBJDIR)

# Listing of phony targets.
.PHONY : all sizebefore sizeafter sdccversion \
		build \
		clean clean_list
