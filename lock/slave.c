#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[]) {
    int fd = open("./lock", O_RDWR);
    printf("try lock... \n");
    if(flock(fd, LOCK_EX) < 0) {
        perror("lock fail.");
        exit(1);
    }
    printf("lock success.\n");
}

