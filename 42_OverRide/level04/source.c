#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int main(void) {
    char    buff[0x20] = {0};
    pid_t   pid;
    int     status;
  
    pid = fork();
    if (pid == 0) {
        prctl(1, 1);
        ptrace(0, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(buff);
    }
    else {
        int ret = ptrace(3, pid, 0x2c, 0);
        while (ret != 0xb) {
            wait(&status);
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                puts("child is exiting...");
                return 0;
            }
        }
        puts("no exec() for you");
        kill(pid, 9);
    }
    return 0;
}
