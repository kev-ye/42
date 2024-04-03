#include <stdio.h>

typedef struct s_u {
    char    msg[140];
    char    uname[40];
    int     len;
}   t_u;

void    secret_backdoor(void) {
    char buff[128];
    
    fgets(buff, 0x80, stdin);
    system(buff);
    return;
}

void    set_msg(t_u *u) {
    char    buff[0x400] = {0};

    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets((char *)buff, 0x400, stdin);
    strncpy(u->msg, buff, u->len);
}


void set_username(t_u *u) {
    char    buff[0x80] = {0};

    puts(">: Enter your username");
    printf(">>: ");
    fgets(buff, 0x80, stdin);
    for (int i = 0; i < 0x29 && buff[i] != '\0'; i++) u->uname[i] = buff[i];
    printf(">: Welcome, %s", u->uname);
    return;
}


void handle_msg(void) {
    t_u u;

    u.len = 140;
    set_username(&u);
    set_msg(&u);
    puts(">: Msg sent!");
    return;
}

int main(void) {
    puts(
        "--------------------------------------------\n"\
        "|   ~Welcome to l33t-m$n ~    v1337        |\n"\
        "- -------------------------------------------"
        );
    handle_msg();
    return 0;
}