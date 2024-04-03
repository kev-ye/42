#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av) {
    FILE    *fd;
    char    buff[132];
    
    fd = fopen("/home/user/end/.pass", "r");

    for (int i = 0; i != 0x21; i++) buff[i] = 0x0;

    if (fd == NULL || ac != 2) return 255;

    fread(buff, 1, 0x42, fd);
    buff[0x41] = 0x0;

    buff[atoi(av[1])] = 0x0;

    fread(buff + 0x42, 1, 0x41, fd);
    fclose(fd);

    if (strcmp(buff, av[1]) == 0) execl("/bin/sh", "sh", 0);
    else puts(buff + 0x42);

    return 0;
}