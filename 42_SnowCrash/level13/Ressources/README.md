# First step

We have a executable file named `level13`.  
```shell
$> ./level13
UID 2013 started us but we we expect 4242  
```

With Ghidra:
```c
void main(void)
{
  __uid_t _Var1;
  undefined4 uVar2;
  
  _Var1 = getuid();
  if (_Var1 != 0x1092) {
    _Var1 = getuid();
    printf("UID %d started us but we we expect %d\n",_Var1,0x1092);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  uVar2 = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
  printf("your token is %s\n",uVar2);
  return;
}
```

# Second step

We gonna use GDB to change uid value.
```shell
$> gdb level13
(gdb) set disassembly-flavor intel
(gdb) b main
(gdb) r
(gdb) disas main
=>  [...]
    0x0804859a <+14>:    cmp    eax,0x1092
    [...]
(gdb) b *0x0804859a
(gdb) disas main
    [...]
=> 0x0804859a <+14>:    cmp    eax,0x1092
    [...]
(gdb) set $eax = 4242
(gdb) c
    your token is 2A31L79asukciNyi8uppkEuSx

$> su level14
```

