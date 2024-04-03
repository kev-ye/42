/*
 * compile with: gcc -m32 -fno-stack-protector -z execstack source.c -o source
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av) {
    int   value;
    char  *exec_name[2];
    uid_t uid;
    gid_t gid;
  
    value = atoi(av[1]);
    if (value == 423) {
        exec_name[0] = strdup("/bin/sh");
        exec_name[1] = NULL;
        gid = getegid();
        uid = geteuid();
        setresgid(gid ,gid, gid);
        setresuid(uid, uid, uid);
        execv("/bin/sh", exec_name);
    }
    else {
        fwrite("No !\n", 1, 5, (FILE *)stderr);
    }
    return 0;
}
