/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdio.h>

void    run(void) {
    fwrite("Good... Wait what?\n", 1, 0x13, stdout);
    system("/bin/sh");
    return;
}

int main(void) {
    char s[76];
  
    gets(s);
    return 0;
}