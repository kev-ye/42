# First step

I was tried to check /etc/shadow but no have access  
I also check the /etc/passwd, nothing except for a hash with flag01  

# Second step

I launch a research to find all flag00 file with 'find' command using -user & -group.

```shell
$> find / -user flag00 -group flag00 2>/dev/null  
/usr/sbin/john
/rofs/usr/sbin/john

$> cat /usr/sbin/john
cdiiddwpgswtgt

$> cat /rofs/usr/sbin/john
cdiiddwpgswtgt
```

Use: 'https://www.dcode.fr/cipher-identifier' to identifier the cipher.
We will know this is a caesar cipher or ROT cipther.  
Brut-the-force using tool in 'dcode' about caesar cipher.    
Only 'nottoohardhere' have some logic sentense.

```shell
$> su flag00
Don't forget to launch getflag !

$> getflag
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
```

