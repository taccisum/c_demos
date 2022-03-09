#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void def() {
    int pipe_fd[2];

    if (pipe(pipe_fd) < 0) {
        perror("fail to create pipe.");
        exit(1);
    } else {
        printf("create pipe success: fd0: %d, fd1: %d\n", pipe_fd[0], pipe_fd[1]);
    }

    if(fork() == 0) {
        printf("child process(%d): waiting for data from pipe...\n", getpid());
        char buf[1024];
        int n = read(pipe_fd[0], buf, sizeof(buf));
        printf("child process(%d): receive data from fd(%d). bytes count: %d, string: %s\n", getpid(), pipe_fd[0], n, buf);
    } else {
        /* sleep 0.5s */
        usleep(500 * 1000);
        char *msg = "hello pipe.";
        long bytes_count = strlen(msg) + 1;        // dont forget send '\0'
        printf("parent process(%d): send data via fd(%d). bytes count: %ld, string: %s\n", getpid(), pipe_fd[1], bytes_count, msg);
        write(pipe_fd[1], msg, bytes_count);
    }
}

int main(int argc,char *argv[]) {
    char *type = argv[1];

    if(type == NULL) {
        def();
    } else {
        /* TODO:: other sample */
    }
}

