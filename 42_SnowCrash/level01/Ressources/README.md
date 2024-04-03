# First step

We have a hash in file /etc/passwd.
Use SCP to get file on local.
```shell
$> scp -P 4242 scp://level01@192.168.64.2/../../../etc/passwd ./myrepo/
```

# Second step

Using john the ripper to brute force the hash.
```shell
$> john passwd
[...]
abcdefg          (flag01)
[...]

$> su flag01
Don't forget to launch getflag !

$> getflag
Check flag.Here is your token : f2av5il02puano7naaf6adaaf
```