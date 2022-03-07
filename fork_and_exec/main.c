#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void fork_and_execvp(char *bin, char *argv[]) {
    int pid;

    if((pid = fork()) < 0) {
        perror("fail to fork new process.");
        exit(1);
    } else if(pid == 0) {
        char cwd[200];
        getcwd(cwd, sizeof(cwd));
        printf("child: do exec %s in cwd '%s'.\n", bin, cwd);

        if((execvp(bin, argv))) {
            printf("fail to exec %s.", bin);
        } else {
            // successed exec always no any return.
            // so this line above is no effect.
            printf("exec %s finished.\n", bin);
        }
    } else {
        int stat_loc;
        if ((pid = wait(&stat_loc)) >= 0) {
            // wait for child process terminated.
            printf("child process %d finished.\n", pid);
        }
    }
}

int main(int argc,char *argv[]) {
    printf("----- exec echo -----\n");
    fork_and_execvp("echo", (char *[]){"echo", "hello", "exec(...)", NULL});

    printf("----- exec cat -----\n");
    fork_and_execvp("/bin/cat", (char *[]){"cat", "Makefile", NULL});

    printf("----- end -----\n");
    printf("do fork & exec finished.\n");
}

