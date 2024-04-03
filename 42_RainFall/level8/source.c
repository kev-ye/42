/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *auth;
static char *service;

int main() {
    char    buffer[128];
    int     i;

    while (1) {
        printf("%p, %p \n", auth, service);

        if (fgets(buffer, 0x80, stdin) == NULL) break;

        i = 0;
        while (buffer[i] == "auth "[i] && i < 5) ++i;
        if (i == 5) {
            auth = malloc(4);
            *auth = 0x0;

            int j = 0;
            while (buffer[i++]) ++j;
            if (j <= 0x1e) strcpy(auth, buffer + 5);
        }

        i = 0;
        while (buffer[i] == "reset"[i] && i < 5) ++i;
        if (i == 5) free(auth);

        i = 0;
        while (buffer[i] == "service"[i] && i < 6) ++i;
        if (i == 6) service = strdup(buffer + 7);

        i = 0;
        while (buffer[i] == "login"[i] && i < 5) ++i;
        if (i == 5) {
            if (auth[32] == 0) fwrite("Password:\n", 0xa, 0x1, stdout);
            else system("/bin/sh");
        }
    }
    return 0;
}