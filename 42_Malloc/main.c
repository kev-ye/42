#include "malloc.h"
// #include <stdlib.h>
#include <string.h>


int main(void) {
    malloc(16);
    show_alloc_mem_info();

    char *s = malloc(10000);
    show_alloc_mem_info();

    s = realloc(s, 524212);
    show_alloc_mem_info();

    free(s);

    show_alloc_mem_leak();
    return (0);
}