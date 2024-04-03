```shell
$> ls -la
[...]
-rwsr-s---+ 1 level07 users   7907 Sep 10  2016 level06
[...]

$> ./level06
***********************************
*               level06           *
***********************************
-> Enter Login: blabla
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: blabla
```

Analyze with ghidra and disassembler the code in GDB

```c
// check source.c file
// with ghidra we can see that the program ask for login and serial
// in auth() function, it create a new secret key by login string and compare it with the serial
// we just need to find the secret key (use a simple printf)
```

```shell
# no interesting thing found in GDB
```

```shell
$> clang source.c && ./a.out
***********************************
*               level06           *
***********************************
-> Enter Login: aaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 1
value: 6231562

# with aaaaaa as login, we can know that the secret key is 6231562

$> ./level06
***********************************
*               level06           *
***********************************
-> Enter Login: aaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6231562
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```