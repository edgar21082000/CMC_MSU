CC = gcc
CFLAGS = -Wall -O2
OBJECTS = main.o func_main.o calculation.o arithmetic.o
TARGET = project.exe
.PHONY: all clean

all: $(TARGET)

project.exe: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) 

%.o : %.c
	$(CC) -c $(CFLAGS) $<   
clean:
	rm $(OBJECTS)
