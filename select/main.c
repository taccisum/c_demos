#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <fcntl.h>

int main(int argc,char *argv[]) {
    char *tty1_p = argv[1];
    char *tty2_p = argv[2];

    int tty1, tty2;

    printf("open tty1: %s\n", tty1_p);
    if ((tty1 = open(tty1_p, O_RDWR)) < 0) {
        perror("fail to open tty1");
        exit(tty1);
    }

    printf("open tty2: %s\n", tty2_p);
    if ((tty2 = open(tty2_p, O_RDWR)) < 0) {
        perror("fail to open tty2");
        exit(tty2);
    }

    printf("fds:%d(tty1), %d(tty2)\n", tty1, tty2);

    struct fd_set fds;
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    int r;
    char buf[1024];

    do {
        /* must do init fds in every loop! */
        FD_ZERO(&fds);
        FD_SET(tty1, &fds);
        FD_SET(tty2, &fds);

        /* block until any fd event */
        r = select(100, &fds, NULL, NULL, &tv);

        if (r < 0) {
            /* select fail, continue next loop */
            continue;
        } else if (r > 0) {
            int fd;
            if(FD_ISSET(tty1, &fds)) {
                fd = tty1;
            } else if(FD_ISSET(tty2, &fds)) {
                fd = tty2;
            } else {
                fd = -1;
            }

            if (fd < 0) {
                continue;
            } else {
                printf("read from fd: %d\n", fd);
            }

            int num = read(fd, buf, sizeof(buf));

            if(num) {
                for(int i = 0; i < num; i++) {
                    putc(buf[i], stdout);
                }

                putc('\n', stdout);
                fflush(stdout);
            } else {
                printf("read fd %d error.\n", fd);
                exit(1);
            }
        } else {
            perror("select timeout(5s). exit program.");
            exit(r);
        }
    } while(1);
}

