#include <stdio.h>

static char a_user_name[100];

int verify_user_pass(char *param_1) {
    return strncmp(param_1, "admin", 5);
}


int verify_user_name(void) {
    puts("verifying username....\n");
    return strncmp(a_user_name, "dat_wil", 7);
}

int main(void) {
    char    buff[64] = {0};
    int     verify;
  
    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(a_user_name, 0x100, stdin);

    verify = verify_user_name();
    if (verify == 0) {
        puts("Enter Password: ");
        fgets(buff, 100, stdin);
        verify = verify_user_pass(buff);
        if ((verify == 0) || (verify != 0)) {
            puts("nope, incorrect password...\n");
            return 1;
        }
        else return 0;
    }
    else {
        puts("nope, incorrect username...\n");
        return 1;
    }
    return 0;
}