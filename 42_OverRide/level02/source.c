#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char    input_pass[112] = {0};
    char    real_pass[48] = {0};
    char    username[112] = {0};
    int     str_end = 0;

    FILE *fd = fopen("/home/users/level03/.pass","r");
    if (fd == (FILE *)0x0) {
        fwrite("ERROR: failed to open password file\n",1,0x24,stderr);
                        /* WARNING: Subroutine does not return */
        exit(1);
    }
    
    int pass_len = fread(real_pass, 1, 0x29, fd);
    str_end = strcspn((char *)real_pass, "\n");
    real_pass[str_end] = '\0';

    if (pass_len != 0x29) {
        fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
        fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
                        /* WARNING: Subroutine does not return */
        exit(1);
    }
    fclose(fd);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(username, 100, stdin);
    int str_end = strcspn((char *)username,"\n");
    username[str_end] = '\0';

    printf("--[ Password: ");
    fgets((char *)input_pass, 100, stdin);
    str_end = strcspn((char *)input_pass,"\n");
    input_pass[str_end] = '\0';

    puts("*****************************************");

    if (strncmp(real_pass, input_pass, 0x29) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
        return 0;
    }
    printf(username);
    puts(" does not have access!");
                        /* WARNING: Subroutine does not return */
    exit(1);
}