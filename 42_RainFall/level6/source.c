/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*fp)(void);

void    n(void) {
  system("/bin/cat /home/user/level7/.pass");
  return;
}

void    m(void) {
  puts("Nope");
  return;
}

int main(int ac, char **av) {
  char  *dest;
  fp    *f;
  
  dest = malloc(0x40);
  f = malloc(4);
  *f = &m;
  strcpy(dest, av[1]);
  (*f)();
  return 0;
}
