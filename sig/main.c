#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void on_exit0() {
    printf("👋 goodbye~\n");
}

void on_exit(int sig) {
    on_exit0();
}

void on_sigusr1(int sig) {
    printf("process %d receive signal: %d\n", getpid(), sig);
}

int main(int argc,char *argv[]) {
    signal(SIGUSR1, on_sigusr1);
    signal(SIGINT, on_exit);

    if(fork() == 0) {
        printf("child process %d start...\n", getpid());
        int ppid = getppid();
        printf("1st child process %d send user-defined signal %d to parent process.\n", getpid(), SIGUSR1);
        printf("2rd child process %d send user-defined signal %d to parent process.\n", getpid(), SIGUSR1);
        kill(ppid, SIGUSR1);
    } else {
        atexit(on_exit0);
        wait(NULL);
        printf("parent process exit.\n");
    }
}

