#!/bin/bash -eux

rm -f main

find src -name '*.c'

gcc \
	-I./src/ \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	main.c \
	src/module/**/**/*.c \
	src/module/plugin/**/**/*.c \
	src/module/plugin/**/**/**/*.c \
	-lnapc-aarch64 \
	-o main
