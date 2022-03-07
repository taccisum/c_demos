#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]) {
    int pid;
    if((pid = fork()) < 0) {
        perror("fail to fork new process.");
        exit(1);
    } else if (pid == 0) {
        printf("child process(pid %d) say: hello.\n", pid);
    } else {
        printf("parent process(pid %d) say: hello.\n", pid);
    }
}

