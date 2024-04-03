/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void p(void) {
    void    *retaddr;
    char    buff[76];
    
    fflush(stdout);
    gets(buff);
    retaddr = __builtin_return_address(0);
    /*
     * 0x080484f2 <+30>:    mov    eax,DWORD PTR [ebp+0x4]
     * [...]
     * 0x080484fb <+39>:    and    eax,0xb0000000
     * 0x08048500 <+44>:    cmp    eax,0xb0000000
     * 
     * [ebp+0x4] means the address of the current function's return.
     * And __builtin_return_address() is the only way to get the return address of the current function.
     */
    if (((unsigned int)retaddr & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", retaddr);
        _exit(1);
    }
    puts(buff);
    strdup(buff);
    return;
}

int main(void){
    p();
    return 0;
}