/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void    p(char *buf, char *sep) {
    char reader[0x1000];
    char *p;
    
    puts(sep);
    read(0, reader, 0x1000);

    p = strchr(reader, '\n');
    *p = '\0';

    strncpy(buf, reader, 0x14);
}

void    pp(char *buf) {
    char s1[20];
    char s2[20];

    p(s1, " - ");
    p(s2, " - ");

    strcpy(buf, s1);
    buf[strlen(buf)] = ' ';

    strcat(buf, s2);
}

int main() {
    char s[54];

    pp(s);
    puts(s);
    return 0;
}
