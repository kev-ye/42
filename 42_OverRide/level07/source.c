#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void    clear_stdin(void) {
  int c;
  
  do {
    c = getchar();
    if ((char)c == '\n') {
      return;
    }
  } while ((char)c != -1);
}

size_t get_unum(void) {
  size_t    value;
  
  value = 0;
  fflush(stdout);
  scanf("%zu", &value);
  clear_stdin();
  return value;
}


int store_number(size_t *buff) {
    size_t    n;
    size_t    i;
    
    printf(" Number: ");
    n = get_unum();

    printf(" Index: ");
    i = get_unum();

    if ((i % 3 == 0) || (n >> 0x18 == 0xb7)) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }
    else {
        buff[i] = n;
        return 0;
    }
}


int read_number(size_t *buff) {
    int value;

    printf(" Index: ");
    value = get_unum();
    printf(" Number at data[%zu] is %zu\n", value, buff[value]);
    return 0;
}


int main(int ac, char **av, char **env) {
    size_t  buff[100] = {0};
    char    cmd[20] = {0};
    int     ret = 0;

    for (int i = 0; av[i] != NULL; i++) memset(av[i], 0, strlen(av[i]));
    for (int i = 0; env[i] != NULL; i++) memset(env[i], 0, strlen(env[i]));

    puts(
        "----------------------------------------------------\n"\
        "  Welcome to wil\'s crappy number stora ge service!   \n"\
        "----------------------------------------------------\n"\
        " Commands:                                           \n"\
        "    store - store a number into the data storage    \n"\
        "    read   - read a number from the data storage     \n"\
        "    quit  - exit the program                         \n"\
        "----------------------------------------------------\n"\
        "   wil has reserved some storage :>                  \n"\
        "----------------------------------------------------\n"
    );

    while (1) {
        printf("Input command: ");
        fgets(cmd, 0x14, stdin);
        cmd[strlen(cmd) - 2] = '\0';

        ret = 1;
        if (strncmp("store", cmd, 5) == 0) ret = store_number(buff);
        else if (strncmp("read", cmd, 4) == 0) ret = read_number(buff);
        else if (strncmp("quit", cmd, 4) == 0) return 0;

        if (ret == 0) printf(" Completed %s command successfully\n", buff);
        else printf(" Failed to do %s command\n", buff);

        memset(cmd, 0, sizeof(cmd));
    }
}