AS31_MK_FILE		:= $(realpath $(lastword $(MAKEFILE_LIST)))
AS31_PATH		:= $(shell dirname $(AS31_MK_FILE))

# Target file name
TARGET			?=

# Define output file
OUTPUT			?= $(addprefix $(BINDIR)/, $(TARGET))

# Output directories
BINDIR			?= bin
OBJDIR			?= obj

# Define all Assembler source files.
ASRCS			+=

# Assembler Options
ASFLAGS			+= -Fhex
ASFLAGS			+= -l

# Define programs and commands.
AS			:= as31
REMOVE			:= rm -rf
COPY			:= cp

# Define all object files.
AOBJS			:= $(addprefix $(OBJDIR)/, $(ASRCS:.asm=.ihx))

# Define Messages
MSG_FLASH		:= Creating load file for Flash:
MSG_LINKING		:= Linking:
MSG_ASSEMBLING		:= Assembling:
MSG_CLEANING		:= Cleaning project:

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_ASFLAGS		:= $(ASFLAGS)

all: build

build: as31version $(BINDIR) $(OBJDIR) output

output: hex

hex: $(OUTPUT).hex $(OUTPUT).bin

as31version:
	@echo -n "$(AS) : "
	@echo `$(AS) -v`

$(BINDIR) $(OBJDIR):
	@mkdir -p $@

%.bin: %.hex
	@echo
	@echo $(MSG_FLASH) "Binary"
	srec_cat $< -Intel -o $@ -Binary

$(OUTPUT).hex: $(AOBJS) | $(BINDIR)
	@echo
	@echo $(MSG_LINKING)
	srec_cat `echo -n "$^ " | perl -pe 's/(\S+\.ihx) /$$1 -Intel /g'` -o $@ -Intel

# Assemble: create object files from assembler source files
$(AOBJS): $(OBJDIR)/%.ihx: %.asm | $(OBJDIR)
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(AS) $(ALL_ASFLAGS) -O$@ $<
	@if [ -e $(<:.asm=.lst) ]; then mv $(<:.asm=.lst) $(OBJDIR)/; fi

# Target: clean project.
clean: clean_list

clean_list:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(BINDIR)
	$(REMOVE) $(OBJDIR)

# Listing of phony targets.
.PHONY : all a31-version \
		build \
		clean clean_list
