CFLAGS=-m32 -g
AFLAGS=-f elf -g -F dwarf

build:	tema2

tema2:	tema2.o include/macro.o include/utils.o
	gcc $^ -o $@ $(CFLAGS)

tema2.o:tema2.asm
	nasm $^ -o $@ $(AFLAGS)

clean:
	rm -rf tema2.o tema2
