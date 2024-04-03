#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void    log_wrapper(FILE *stream, char *msg,char *file_name) {
    char buff[264];
    
    strcpy(buff, msg);
    snprintf(buff[strlen(buff) - 1], 0xfe - (strlen(buff) - 1), file_name);
    buff[strcspn(buff, "\n")] = '\0';
    fprintf(stream, "LOG: %s\n", buff);
}


int main(int ac, char *av[]) {
    char    buff[100];

    if (ac != 2) printf("Usage: %s filename\n", *av);

    FILE *log = fopen("./backups/.log", "w");
    if (log == NULL) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
                        /* WARNING: Subroutine does not return */
        exit(1);
    }

    log_wrapper(log, "Starting back up: ", av[1]);

    FILE *file = fopen(av[1], "r");
    if (file == NULL) {
        printf("ERROR: Failed to open %s\n", av[1]);
                        /* WARNING: Subroutine does not return */
        exit(1);
    }

    strcpy(buff, "./backups/");
    strncat(buff, av[1], 99 - (strlen(buff) - 1));
    int fd = open(buff, 0xc1, 0x1b0);
    if (fd < 0) {
        printf("ERROR: Failed to open %s%s\n","./backups/",av[1]);
                        /* WARNING: Subroutine does not return */
        exit(1);
    }

    while(1) {
        char c = fgetc(file);
        if ((int)c == -1) break;
        write(fd, &c, 1);
    }

    log_wrapper(log, "Finished back up ", av[1]);
    fclose(file);
    close(fd);

    return 0;
}