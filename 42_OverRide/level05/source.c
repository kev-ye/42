#include <stdio.h>

int main(void) {
    char    buff[100];
    int     i = 0;
    
    fgets(buff, 100, stdin);
    while (1) {
        if (i < strlen(buff)) break;

        if (buff[i] > 0x42 && buff[i] < 0x5a ) buff[i] ^= 0x20;
    }

    print(buff);
    exit(0);
}
