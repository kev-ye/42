/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av) {
  char  buff[40];
  int   n;
  
  n = atoi((av[1]));
  if (n < 10) {
    memcpy(buff, av[2], n * 4);
    if (n == 0x574f4c46) execl("/bin/sh", "sh", 0);
  }
  else
    return 1;
  return 0;
}