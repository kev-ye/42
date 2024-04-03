/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdio.h>

static int m;

void    v(void) {
    char buff[520];
    
    printf("before[%d]\n", m);

    fgets(buff, 0x200, stdin);
    printf(buff);

    printf("after[%d]\n", m);
    if (m == 0x40) {
        fwrite("Wait what?!\n", 1, 0xc, stdout);
        system("/bin/sh");
    }
    return;
}

int main(void) {
    v();
    return 0;
}