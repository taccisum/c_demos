#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int dones = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void t_exit() {
    pthread_mutex_lock(&lock);
    dones += 1;     // done thread count +1
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

void t_join(unsigned int count) {
    pthread_mutex_lock(&lock);
    while(dones < count) {
        printf("[%p] dones less than thread count, continue wait.\n", pthread_self);
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);
}

#ifndef __ut
void *runnable() {
    printf("[%p] thread run.\n", pthread_self());
    sleep(1);
    printf("[%p] thread exit.\n", pthread_self());
    t_exit();
    return 0;
}

int main(int argc,char *argv[]) {
    pthread_t t;
    pthread_create(&t, NULL, runnable, NULL);
    pthread_create(&t, NULL, runnable, NULL);
    t_join(2);
}
#endif

