```shell
# GOT / Stack / NX is proctected here so we only can found the solution in the code

$> ls -la
[...]
-rwsr-s---+ 1 level04 users   7677 Sep 10  2016 level03
[...]

$> ./level03 
***********************************
*               level03         **
***********************************
Password:1

Invalid Password
```

Analyze with ghidra and disassembler the code in GDB

```c
// check source.c file
```

```shell
$> gdb -q level03
(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x080488c1 <+103>:   call   0x8048530 <__isoc99_scanf@plt>
    0x080488c6 <+108>:   mov    eax,DWORD PTR [esp+0x1c]
    0x080488ca <+112>:   mov    DWORD PTR [esp+0x4],0x1337d00d
    0x080488d2 <+120>:   mov    DWORD PTR [esp],eax
    0x080488d5 <+123>:   call   0x8048747 <test>
    0x080488da <+128>:   mov    eax,0x0
    [...]

    # call test function with input (%d) and 0x1337d00d as parameters

(gdb) disas test
    [...]
    0x0804874d <+6>:     mov    eax,DWORD PTR [ebp+0x8]
    0x08048750 <+9>:     mov    edx,DWORD PTR [ebp+0xc]
    0x08048753 <+12>:    mov    ecx,edx
    0x08048755 <+14>:    sub    ecx,eax
    0x08048757 <+16>:    mov    eax,ecx
    0x08048759 <+18>:    mov    DWORD PTR [ebp-0xc],eax
    0x0804875c <+21>:    cmp    DWORD PTR [ebp-0xc],0x15
    0x08048760 <+25>:    ja     0x804884a <test+259>
    0x08048766 <+31>:    mov    eax,DWORD PTR [ebp-0xc]
    0x08048769 <+34>:    shl    eax,0x2
    0x0804876c <+37>:    add    eax,0x80489f0
    0x08048771 <+42>:    mov    eax,DWORD PTR [eax]
    0x08048773 <+44>:    jmp    eax
    [...]
    0x08048775 <+46>:    mov    eax,DWORD PTR [ebp-0xc]
    0x08048778 <+49>:    mov    DWORD PTR [esp],eax
    0x0804877b <+52>:    call   0x8048660 <decrypt>
    0x08048780 <+57>:    jmp    0x8048858 <test+273>
    [...]
    0x0804884a <+259>:   call   0x8048520 <rand@plt>
    0x0804884f <+264>:   mov    DWORD PTR [esp],eax
    0x08048852 <+267>:   call   0x8048660 <decrypt>
    [...]

    # switch style of the comparison to call decrypt
    # here if 0x1337d00d - value < 0x15 will call decrypt with the value as parameter
    # else it will decrypt with random value as parameter

(gdb) disas decrypt
    [...]
    0x08048673 <+19>:    mov    DWORD PTR [ebp-0x1d],0x757c7d51
    0x0804867a <+26>:    mov    DWORD PTR [ebp-0x19],0x67667360
    0x08048681 <+33>:    mov    DWORD PTR [ebp-0x15],0x7b66737e
    0x08048688 <+40>:    mov    DWORD PTR [ebp-0x11],0x33617c7d
    [...]
    0x080486c7 <+103>:   lea    eax,[ebp-0x1d]
    0x080486ca <+106>:   add    eax,DWORD PTR [ebp-0x28]
    0x080486cd <+109>:   movzx  eax,BYTE PTR [eax]
    0x080486d0 <+112>:   mov    edx,eax
    0x080486d2 <+114>:   mov    eax,DWORD PTR [ebp+0x8]
    0x080486d5 <+117>:   xor    eax,edx
    0x080486d7 <+119>:   mov    edx,eax
    0x080486d9 <+121>:   lea    eax,[ebp-0x1d]
    0x080486dc <+124>:   add    eax,DWORD PTR [ebp-0x28]
    0x080486df <+127>:   mov    BYTE PTR [eax],dl
    0x080486e1 <+129>:   add    DWORD PTR [ebp-0x28],0x1
    0x080486e5 <+133>:   mov    eax,DWORD PTR [ebp-0x28]
    0x080486e8 <+136>:   cmp    eax,DWORD PTR [ebp-0x24]
    0x080486eb <+139>:   jb     0x80486c7 <decrypt+103>
    [...]
    0x080486ed <+141>:   lea    eax,[ebp-0x1d]
    0x080486f0 <+144>:   mov    edx,eax
    0x080486f2 <+146>:   mov    eax,0x80489c3
    0x080486f7 <+151>:   mov    ecx,0x11
    0x080486fc <+156>:   mov    esi,edx
    0x080486fe <+158>:   mov    edi,eax
    0x08048700 <+160>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
    [...]

    # a string containning the encrypted value "Q}|u`sfg~sf{}|a3"
    # a loop will decrypt the string with XOR operation
    # a strncmp will compare the decrypted string with the value "Congratulations!"
    # if true, it will execute the system("/bin/sh")
    # else it will print "Invalid Password"
    # so we need to find the value of the input to decrypt the string "Q}|u`sfg~sf{}|a3"
    # after some test, we found 18 (0x12), so 0x1337d00d - 0x12 = 0x1337cffb (322424827)
```

```shell
$> ./level03
***********************************
*               level03         **
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```