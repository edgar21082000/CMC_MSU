#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
    char name[64];
    char str[8192];
    strcpy(name, argv[1]);
    int fd = creat("makefile", 0777);
    str[0] = 0;
    strcat(str, "TARGET = ");
    strcat(str, name);
    strcat(str, ".e\n\n");
    strcat(str, "PROG_OBJ = ");
    strcat(str, name);
    strcat(str, ".o\n\n");
    strcat(str, "C_FLAGS = -std=c99 -c -m32 -o -Wall -Werror\n\n");
    strcat(str, "all: $(TARGET)\n\n");
    strcat(str, "run: $(TARGET)\n\t./$(TARGET)\n\n");
    strcat(str, "clean:\n\trm -f $(PROG_OBJ\n\n");
    strcat(str, "$(TARGET): $(PROG_OBJ)\n\tgcc -o $(TARGET) $(PROG_OBJ) -m32\n");
    strcat(str, "%.o: %.c\n\tgcc $(C_FLAGS) $@ $<\n");

    write(fd, str, strlen(str));
    close(fd);
    return 0;
}
