#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int main(int argc,char *argv[]) {
    char *msg = "hello";

    for(int i = 0; i < strlen(msg); i++) {
        putc(msg[i], stdout);
        fflush(stdout);
        usleep(200000);
    }

    for(int i = 0; i < strlen(msg); i++) {
        putc('\b', stdout);
        fflush(stdout);
        usleep(200000);
    }
}

