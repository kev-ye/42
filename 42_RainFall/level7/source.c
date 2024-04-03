/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct s_struct {
    int     i;
    char    *s;
} t_struct;

static char c[68];

void    m(void) {
    time_t  t;
    
    t = time((time_t *)0x0);
    printf("%s - %d\n", c, t);
    return;
}

int main(int ac, char **av) {
    t_struct    *s1;
    t_struct    *s2;
    FILE        *stream;
    
    s1 = malloc(8);
    s1->i = 1;
    s1->s = malloc(8);

    s2 = malloc(8);
    s2->i = 2;
    s2->s = malloc(8);

    strcpy(s1->s, av[1]);
    strcpy(s2->s, av[2]);
    stream = fopen("/home/user/level8/.pass", "r");
    fgets(c, 0x44, stream);
    puts("~~");
    return 0;
}