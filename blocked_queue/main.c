#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t lock;
pthread_cond_t non_empty;
pthread_cond_t non_full;

#define QUEUE_SIZE 10
#define QUEUE_LAST QUEUE_SIZE - 1

int queue[QUEUE_SIZE];
int count, p_sum, c_sum = 0;
/* define pointer left & right */
int left, right = 0;

void *producer() {
    while(1) {
        /* produce one data per second */
        sleep(1);
        pthread_mutex_lock(&lock);

        if(count == 10) {
            printf("[producer] [%p] queue is full now(count %d), await...\n", pthread_self(), count);
            while(count == 10) {
                pthread_cond_wait(&non_full, &lock);
            }
        }
        if(right == QUEUE_LAST) {
            right = 0;
        } else {
            right++;
        }
        queue[right] = 127;
        count++;
        p_sum++;
        printf("[producer] [%p] produce new element. left: %d, right: %d, count: %d. signal other thread queue is non empty now.\n", pthread_self(), left, right, count);
        pthread_cond_signal(&non_empty);
        pthread_mutex_unlock(&lock);
    }
    return 0;
}

void do_consume(int data) {
    /* consume one date per 2 seconds */
    sleep(2);
    printf("[consumer] [%p] consume element '%d' finished.\n", pthread_self(), data);
}

void *consumer() {
    while(1) {
        pthread_mutex_lock(&lock);

        if(count == 0) {
            printf("[consumer] [%p] queue is empty now(count %d), await...\n", pthread_self(), count);
            while(count == 0) {
                pthread_cond_wait(&non_empty, &lock);
            }
        }
        int take = queue[left];

        if(left == QUEUE_LAST) {
            left = 0;
        } else {
            left++;
        }
        count--;
        c_sum++;
        printf("[consumer] [%p] take element: %d. left: %d, right: %d, count: %d. signal other thread queue is non full now.\n", pthread_self(), take, left, right, count);

        pthread_cond_signal(&non_full);
        pthread_mutex_unlock(&lock);

        // do consume after unlock
        do_consume(take);
    }
    return 0;
}

#ifndef __ut
int main(int argc,char *argv[]) {
    pthread_t t_pro;
    pthread_t t_con0;
    pthread_t t_con1;
    /* one producer */
    pthread_create(&t_pro, NULL, producer, NULL);
    /* two consumer */
    pthread_create(&t_con0, NULL, consumer, NULL);
    pthread_create(&t_con1, NULL, consumer, NULL);

    sleep(5);
    pthread_cancel(t_pro);
    pthread_cancel(t_con0);
    pthread_cancel(t_con1);
    printf("[main] [stop] 5s elasped. produce count: %d, consume count: %d.\n", p_sum, c_sum);
    exit(0);
}
#endif

