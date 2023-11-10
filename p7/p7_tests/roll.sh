#!/bin/bash
as -o $1.o $1
ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
                /usr/lib/x86_64-linux-gnu/crt1.o \
		        /usr/lib/x86_64-linux-gnu/crti.o \
		        -lc \
		        $1.o \
		        ../stdjeff.o \
		        /usr/lib/x86_64-linux-gnu/crtn.o \
		        -o  $1.prog
