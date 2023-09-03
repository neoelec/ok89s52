# Hey Emacs, this is a -*- makefile -*-

# Output FORMAT.
#   hex   :
#   tdr   :
#   byte  :
#   od    :
#   srec2 :
#   srec3 :
#   srec4 :
FORMAT_SUPPORTED:= hex tdr byte od srec2 srec3 srec4
FORMAT		:= hex


# Target file name
TARGET		?= paulmon21


# Define all Assembler source files.
ASRCS		:= $(TARGET).asm extra.asm


# Output directories
BINDIR		:= bin
OBJDIR		:= obj


# Assembler Options
ASFLAGS		:= -F$(FORMAT)
ASFLAGS		+= -l



# Define programs and commands.
AS		:= as31
REMOVE		:= rm -rf


# Define all object files.
AOBJS		:= $(addprefix $(OBJDIR)/, $(ASRCS:.asm=.rel))


# Define output file
fmt_ext_hex	:= hex
fmt_ext_tdr	:= tdr
fmt_ext_byte	:= byte
fmt_ext_od	:= od
fmt_ext_srec2	:= srec
fmt_ext_srec3	:= srec
fmt_ext_srec4	:= srec

fmt_eof_hex	:= :00000001FF
fmt_eof_srec2	:= :S9030000FC
fmt_eof_srec3	:= :S804000000FB
fmt_eof_srec4	:= :S70500000000FA

define define_output
output_$(1)	:= $(addprefix $(BINDIR)/, $(TARGET).$($(addprefix fmt_ext_,$(1))))
endef

$(foreach fmt,$(FORMAT_SUPPORTED),$(eval $(call define_output,$(fmt))))

OUTPUT		:= $($(addprefix output_,$(FORMAT)))
OUTPUT_EOF	:= $($(addprefix fmt_eof_,$(FORMAT)))


# Define Messages
MSG_BEGIN	:= -------- begin --------
MSG_END		:= --------  end  --------
MSG_MERGING	:= Merging:
MSG_ASSEMBLING	:= Assembling:
MSG_CLEANING	:= Cleaning project:


# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_ASFLAGS	:= $(ASFLAGS)


all: build


build: as31-version begin $(BINDIR) $(OBJDIR) $(OUTPUT) end


as31-version:
	@echo "$(AS) : "
	@echo `$(AS) -v`


begin:
	@echo
	@echo $(MSG_BEGIN)


end:
	@echo
	@echo $(MSG_END)
	@echo


$(BINDIR) $(OBJDIR):
	mkdir $@


$(OUTPUT): $(AOBJS)
	@echo
	@echo $(MSG_MERGING) $(OUTPUT)
	@echo " - output-format: $(FORMAT)"
	@if [ -z $(OUTPUT_EOF) ]; then \
		cat $^ > $@; \
	else \
		cat $^ | sed -e '/$(OUTPUT_EOF)/d' > $@; \
		echo "$(OUTPUT_EOF)" >> $@; \
	fi


# Assemble: create object files from assembler source files
$(AOBJS): $(OBJDIR)/%.rel: %.asm
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(AS) $(ALL_ASFLAGS) -O$@ $<
	@if [ -e $(<:.asm=.lst) ]; then mv $(<:.asm=.lst) $(OBJDIR)/; fi


# Target: clean project.
clean: begin clean_list end


clean_list:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(BINDIR)
	$(REMOVE) $(OBJDIR)


# Listing of phony targets.
.PHONY : clean begin all end a31-version
