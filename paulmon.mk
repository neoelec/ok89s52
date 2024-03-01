# Hey Emacs, this is a -*- makefile -*-

# Define TTY Device.
TTY_DEV			?= /dev/ttyUSB0

pm21_upload: build
	@ascii-xfr -s -l 5 -c 5 $(OUTPUT) > $(TTY_DEV)

# Listing of phony targets.
.PHONY : pm21_upload
