/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdio.h>

static int m;

void    p(char *buffer) {
  printf(buffer);
  return;
}

void    n(void) {
  char buffer[520];
  
  fgets(buffer, 0x200, stdin);
  p(buffer);
  if (m == 0x1025544) {
    system("/bin/cat /home/user/level5/.pass");
  }
  return;
}

int main(void) {
  n();
  return 0;
}
