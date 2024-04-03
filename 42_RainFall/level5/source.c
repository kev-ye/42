/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdio.h>
#include <stdlib.h>

void    o(void) {
    system("/bin/sh");
    _exit(1);
}


void    n(void) {
    char buffer[520];
    
    fgets(buffer ,0x200, stdin);
    printf(buffer);
    exit(1);
}

int main(void) {
    n();
    return 0;
}
