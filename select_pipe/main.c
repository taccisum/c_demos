#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

static char *fifos[] = {"fifo1", "fifo2", "fifo3", NULL};

void clear_fifos() {
    int i = 0;

    while(fifos[i] != NULL) {
        char *path = fifos[i];
        struct stat buf;
        int n = stat(path, &buf);
        if(n == 0) {
            remove(path);
        }
        i++;
    }
}

void create_fifos() {
    int i = 0;

    while(fifos[i] != NULL) {
        char *path = fifos[i];
        mkfifo(path, S_IRWXU);
        i++;
    }
}

int main(int argc,char *argv[]) {
    /* clear_fifos(); */
    /* create_fifos(); */
    /* atexit(clear_fifos); */

    int fifo1, fifo2, fifo3;

    printf("open fifo files...\n");
    if ((fifo1 = open("fifo1", O_RDONLY | O_NONBLOCK)) < 0) {
        perror("fail to open fifo1");
        exit(fifo1);
    }
    if ((fifo2 = open("fifo2", O_RDONLY | O_NONBLOCK)) < 0) {
        perror("fail to open fifo2");
        exit(fifo2);
    }
    if ((fifo3 = open("fifo3", O_RDONLY | O_NONBLOCK)) < 0) {
        perror("fail to open fifo3");
        exit(fifo3);
    }

    printf("fds:%d(fifo1), %d(fifo2), %d(fifo3)\n", fifo1, fifo2, fifo3);

    struct fd_set fds;
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    int r;
    char buf[1024];

    printf("do select() loop...\n");
    do {
        /* must do init fds in every loop! */
        FD_ZERO(&fds);
        FD_SET(fifo1, &fds);
        FD_SET(fifo2, &fds);
        FD_SET(fifo3, &fds);

        /* block until any fd event */
        r = select(100, &fds, NULL, NULL, &tv);

        if (r < 0) {
            /* select fail, continue next loop */
            continue;
        } else if (r > 0) {
            int fd;
            if(FD_ISSET(fifo1, &fds)) {
                fd = fifo1;
            } else if(FD_ISSET(fifo2, &fds)) {
                fd = fifo2;
            } else if(FD_ISSET(fifo3, &fds)) {
                fd = fifo3;
            } else {
                continue;
            }

            int num = read(fd, buf, sizeof(buf));
            if(num > 0) {
                printf("read %d bytes from fd: %d\n", num, fd);
                buf[num] = '\0';        // set end of bytes '\0', assure accurate output via printf
                printf("%s", buf);
            } else if (num < 0) {
                perror("read fd error");
                exit(num);
            }
        } else if (r == 0){
            printf("select timeout(5s).\n");
            exit(r);
        } else {
            perror("select failed.");
            exit(r);
        }
    } while(1);
}

