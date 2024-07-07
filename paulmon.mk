# Hey Emacs, this is a -*- makefile -*-

# Define TTY Device.
TTY_DEV			?= /dev/ttyUSB0

MSG_PAULMON		:= Upload to PAULMON v2.1:

paulmon: build
	@echo
	@echo $(MSG_PAULMON) $(OUTPUT).hex
	@ascii-xfr -s -l 1 -c 1 $(OUTPUT).hex > $(TTY_DEV)

# Listing of phony targets.
.PHONY : paulmon
