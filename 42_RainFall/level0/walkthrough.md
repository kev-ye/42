```shell
$> ls -la
[...]
-rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0
[...]

$> ./level0
Segmentation fault (core dumped)

$> ./level0 test
No !

$> ./level0 123
No !

$> ./level0 blabla 123
No !
```

We can see a executable executed with an argument.
Let's read source code with GDB.

```shell
$> gdb level0
(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x08048ed4 <+20>:    call   0x8049710 <atoi>
    0x08048ed9 <+25>:    cmp    eax,0x1a7
    [...]

# executable use atoi() to convert a string to an integer
# and compare it with a 0x1a7 (423)
# let's try with 423 as argument

$> ./level0 423
$ whoami
level1
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```