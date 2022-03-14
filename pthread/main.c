#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

/* thread arguments */
struct t_args {
    int no;
    char *greeting;
    char *name;
};

/* runnable function */
int *run(struct t_args *args) {
    pthread_t tid = pthread_self();
    printf("thread[no: %d, tid: %p, args: %p], %s, %s.\n", args->no, tid, args, args->greeting, args->name);
    return 0;
}

int main(int argc,char *argv[]) {
    pthread_t tid;

    for (int i = 0; i < 5; i++) {
        struct t_args *args = malloc(sizeof(struct t_args));
        args->no = i;
        args->greeting = "hello";
        args->name = "taccisum";

        int r;
        if ((r = pthread_create(&tid, NULL, (void *)run, args)) == 0) {
            printf("thread[%d] created. tid: %p\n", i, tid);
        } else {
            strerror(r);
            exit(r);
        }
    }

    /* use pthread_exit() instead exit() to wait all threads exit */ 
    pthread_exit(0);
}

