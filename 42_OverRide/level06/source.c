#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

size_t  auth(char *buff, size_t value) {
    size_t tmp = strcspn(buff,"\n");
    buff[tmp] = '\0';

    size_t len = strnlen(buff, 0x20);
    if (tmp < 6) return 1;
    
    if (ptrace(0, 0, (caddr_t)1, 0) == -1) {
        puts("\x1b[32m.---------------------------.");
        puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1b[32m\'---------------------------\'");
        return 1;
    }

    tmp = ((int)buff[3] ^ 0x1337U) + 0x5eeded;
    for (int i = 0; i < (int)len; i = i + 1) {
        if (buff[i] < ' ') return 1;
        tmp = tmp + ((int)buff[i] ^ tmp) % 0x539;
    }
    // printf("value: %zu\n", tmp);
    if (value != tmp) return 1;

    return 0;
}

int main(void) {
    char    buff[32];
    size_t  value;
  
    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");

    fgets(buff, 0x20, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");

    scanf("%zu", &value);

    if (auth(buff, value) == 0) {
        puts("Authenticated!");
        system("/bin/sh");
    }
    return value != 0;
}