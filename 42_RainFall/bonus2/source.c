/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdlib.h>
#include <string.h>

static int language;

void    greetuser(char *buff) {
    char s[72];

    if (language == 0) {
        char *msg = "Hello ";
        for (int i = 0; i < 6; i++) s[i] = msg[i];
    }
    else if (language == 1) {
        char *msg = "Hyvää päivää ";
        for (int i = 0; i < 18; i++) s[i] = msg[i];
    }
    else if (language == 2) {
        char *msg = "Goedemiddag! ";
        for (int i = 0; i < 12; i++) s[i] = msg[i];
    }

    strcat(s, buff);
    puts(s);
}

int main(int ac, char **av) {
    char buff[72];
    
    if (ac != 3)
        return 1;

    for (int i = 0; i <= 0x13; i++) buff[i] = 0x0;

    strncpy(buff, av[1], 0x28);
    strncpy(buff + 40, av[2], 0x20);

    char *lang = getenv("LANG");
    if (lang != NULL) {
        if (memcmp(lang, "fi", 2) == 0) language = 1;
        else if (memcmp(lang, "nl", 2) == 0) language = 2;
    }
    
    char *ptr;

    for (int i = 0; i <= 0x13; i++) ptr[i] = buff[i];
    
    greetuser(buff);
    return 0;
}
