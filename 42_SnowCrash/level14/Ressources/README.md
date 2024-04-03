# First step

No interesting file here.  
Let's break /bin/getflag.  
    -> some analyze with ghidra  
        -> we can know it compare with uid to get flag  
Let's use GDB as level13.  

# Second step

```shell
$> gdb getflag
(gdb) set disassembly-flavor intel
(gdb) b main
(gdb) r
(gdb) disas main
    [...]
=>  0x08048b0a <+452>:   cmp    eax,0xbbe
    [...]
(gdb) b *0x08048b0a
(gdb) jump *0x08048b0a
(gdb) set $eax = 3014
(gdb) c
    7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
    [...]

$> su flag14
Congratulation. Type getflag to get the key and send it to me the owner of this livecd :)

$> getflag
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```