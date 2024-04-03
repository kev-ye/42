#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decrypt(int value) {
    char str[] = "Q}|u`sfg~sf{}|a3";

    int len = strlen(str);

    int i = 0;

    while (i < len) {
        str[i] = str[i] ^ value;
        i++;
    }

    if (strncmp(str, "Congratulations!", 0x17) == 0) system("/bin/sh");
    else puts("\nInvalid Password");
}

void    test(int value, int n) {
    n = n - value;

    switch(n < 0x15) {
        default:
            decrypt(random());
            break;
        case 0x1:
            decrypt(n);
            break;
        case 0x2:
            decrypt(n);
            break;
        case 0x3:
            decrypt(n);
            break;
        case 0x4:
            decrypt(n);
            break;
        case 0x5:
            decrypt(n);
            break;
        case 0x6:
            decrypt(n);
            break;
        case 0x7:
            decrypt(n);
            break;
        case 0x8:
            decrypt(n);
            break;
        case 0x9:
            decrypt(n);
            break;
        case 0x10:
            decrypt(n);
            break;
        case 0x11:
            decrypt(n);
            break;
        case 0x12:
            decrypt(n);
            break;
        case 0x13:
            decrypt(n);
            break;
        case 0x14:
            decrypt(n);
            break;
        case 0x15:
            decrypt(n);
    }
}

int main(void) {  
    int value;

    srand(time(NULL));
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password:");

    scanf("%d", &value);
    test(value, 0x1337d00d);
    return 0;
}