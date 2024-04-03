# First step

We have same file as in level08, but we can read token file.

```shell
$> cat token
f4kmm6p|=�p�n��DB�Du{��  

$> ./level09 token
tpmhr
```

flag get, too easy!!!  
That's joke ...  

After trying launch level09, we get something like ...

```shell
$> ./level09 abc
ace

$> ./level09 aaa
abc
```

We can know the algorithm of the level09.  
For each character in the string, it add current index.  

# Second step

We create a script.py file to decode the token.
```python
import sys

value = sys.argv[1].encode(errors='surrogateescape')
new_value = ''.join([chr(v - i) for i, v in enumerate(value)])
print(new_value)
```

Use scp to get the token file and launch the decode script.

```shell
$> scp -P 4242 scp://level09@192.168.64.2/token ./myrepo/

$> chmod 777 token

$> python script.py `cat token`
f3iji1ju5yuevaus41q1afiuq

$> su flag09
Don't forget to launch getflag !

$> getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```