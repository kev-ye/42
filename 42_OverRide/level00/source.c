#include <stdio.h>
#include <libc.h>

int main(void) {
    int value;
    
    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    printf("Password:");
    scanf("%d", value);
    if (value != 0x149c) puts("\nInvalid Password!");
    else {
        puts("\nAuthenticated!");
        system("/bin/sh");
    }

    return value != 0x149c;
}