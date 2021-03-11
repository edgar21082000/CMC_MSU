#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int main(int argc, char **argv)
{
    const char *path = NULL;
    if (!(path = getenv("XDG_RUNTIME_DIR"))) {
        if(!(path = getenv("TMPDIR"))) {
            path = "/tmp";
        }
    }
        
    int rand = open("/dev/urandom", O_RDONLY, 0);
    char file_name[PATH_MAX];
    
    int fd = -1;
    errno = EEXIST;
    while (errno == EEXIST && fd < 0) {
        unsigned int i;
        read(rand, &i, sizeof(i));
        snprintf(file_name, sizeof(file_name), "%s/script_%u", path, i);
        errno = 0;
        fd = open(file_name, O_CREAT | O_WRONLY | O_EXCL, 0700);
    }
    close(rand);

    FILE *wr = fdopen(fd, "w");
    fprintf(wr, "#!/usr/bin/python3\n");
    fprintf(wr, "import os, sys\n");
    fprintf(wr, "a = %s\n", argv[1]);
    for (int i = 2; i < argc; i++) {
        fprintf(wr, "a *= %s\n", argv[i]);
    }
    fprintf(wr, "print(a)\n");
    fprintf(wr, "os.remove(sys.argv[0])\n"); 
    fclose(wr);  
    execlp(file_name, file_name, NULL);
    _exit(1);
}
