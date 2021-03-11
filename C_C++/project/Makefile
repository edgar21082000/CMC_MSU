OBJECTS=main.o calc.o function.o derivative.o
.PHONY: all clean

all : project.exe

project.exe: $(OBJECTS)
	gcc -o $@ $(OBJECTS) -m32 -lm

%.o : %.c
	gcc -c $< -o $@ -m32 -lm -Dnewton
%.o : %.asm
	nasm -felf32 -o $@ $<
	
clean:
	rm $(OBJECTS)
