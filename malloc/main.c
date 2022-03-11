#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int main(int argc,char *argv[]) {
    if(fork() == 0) {
        int *ptr = malloc(sizeof(int));
        *ptr = 127;
        printf("%d: %p, val: %d\n", getpid(), ptr, *ptr);
        exit(0);
    }
    if(fork() == 0) {
        int *ptr = malloc(sizeof(int));
        *ptr = 126;
        printf("%d: %p, val: %d\n", getpid(), ptr, *ptr);
        exit(0);
    }
    exit(0);
}

