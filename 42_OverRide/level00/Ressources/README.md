```shell
$> ls -la
[...]
-rwsr-s---+ 1 level01 users   7280 Sep 10  2016 level00
[...]

$> ./level00
***********************************
*            -Level00 -           *
***********************************
Password:blabla

Invalid Password!
```

Analyze with ghidra and disassembler the code in GDB

```c
[...]
    if (value != 0x149c) puts("\nInvalid Password!");
    else {
        puts("\nAuthenticated!");
        system("/bin/sh");
    }
[...]

// we can see that the program compare a value with a constant
// and if it is not equal, it prints an error message and exits
// else it execute the system command
```

```shell
$> gdb -q level00
(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x080484ce <+58>:    mov    eax,0x8048636
        [...]
    0x080484de <+74>:    call   0x80483d0 <__isoc99_scanf@plt>
    0x080484e3 <+79>:    mov    eax,DWORD PTR [esp+0x1c]
    0x080484e7 <+83>:    cmp    eax,0x149c
    [...]

# 0x8048636: "%d"
# __isoc99_scanf: scanf
# Here calls scanf and stock the value in eax with the format "%d"
# register eax compare the value with the constant 0x149c
```

```shell
$> ./level00
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ pwd
/home/users/level00
$ whoami       
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```