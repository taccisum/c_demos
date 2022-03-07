#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

void printf0(char *msg, ...) {
    va_list va;
    va_start(va, msg);
    char *arg;

    for (int i = 0; i < strlen(msg); i++) {
        char c = msg[i];
        if(c != '%') {
            write(1, &c, sizeof(char));
        } else {
            arg = va_arg(va, char *);
            if (arg != NULL) {
                write(1, arg, strlen(arg));
            } else {
                // do nothing
            }
        }
    }

    va_end(va);
}

int main(int argc,char *argv[]) {
    printf0("hello %, %, and %\n", "jack", "sam", "taccisum", NULL);
}

