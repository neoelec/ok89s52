# SPDX-License-Identifier: GPL-2.0+
# Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

PAULMON_MK_FILE			:= $(realpath $(lastword $(MAKEFILE_LIST)))
PAULMON_MK_DIR			:= $(shell dirname $(PAULMON_MK_FILE))

# Define TTY Device.
TTY_DEV				?= /dev/ttyUSB0

MSG_PAULMON			:= Upload to PAULMON v2.1:

paulmon: build
	@echo
	@echo $(MSG_PAULMON) $(OUTPUT).hex
	@ascii-xfr -s -l 1 -c 1 $(OUTPUT).hex > $(TTY_DEV)

# Listing of phony targets.
.PHONY : paulmon
