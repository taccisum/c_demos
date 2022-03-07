#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

int main(int argc,char *argv[]) {
    printf("you can run command: 'ps -o state,pid,ppid,uid,command' to show state of child processes in the meanwhile.\n");

    if (fork() == 0) {
        printf("child process 1: finished. will become a zombie process after exit.\n");
        exit(0);
    } else {
        printf("parent process: sleep 5s...\n");
        sleep(5);
    }

    if (fork() == 0) {
        printf("child process 2: running...\n");
        printf("child process 2: sleep 10s, waiting for parent process exit...\n");
        sleep(10);
        printf("child process 2: finished.\n");
        exit(0);
    } else {
        printf("parent process: sleep 5s...\n");
        sleep(5);
        printf("parent process: finished.\n");
    }
}

