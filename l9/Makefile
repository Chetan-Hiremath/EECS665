SIMPLE_ASM=-fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm -fno-exceptions -fno-rtti

all: 
	g++ example.cpp -s -S -O0 $(SIMPLE_ASM)
	cat example.s | c++filt > filtered.s
	g++ example.s -o example

clean:
	rm -f example.s filtered.s example

