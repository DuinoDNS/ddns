#!/bin/bash

./compile.sh

NAPC_ETH_LINK_STATUS_FILE=/tmp/ddns_link_status \
NAPC_FILE_ROOT_PATH=TEST_SDCARD/ \
valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	./main
