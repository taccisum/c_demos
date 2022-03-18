/* avoid conflicted function main definitions */
#define __ut

/* unit test framework */
#include "../lib/minunit.h"

/* blocked_queue.c test suite start */
#include "../blocked_queue/main.c"

MU_TEST(bq_index) {
    pthread_t t_pro;
    pthread_t t_con0;
    pthread_t t_con1;
    /* one producer */
    pthread_create(&t_pro, NULL, producer, NULL);
    /* two consumer */
    pthread_create(&t_con0, NULL, consumer, NULL);
    pthread_create(&t_con1, NULL, consumer, NULL);

    sleep(4);
    pthread_cancel(t_pro);
    pthread_cancel(t_con0);
    pthread_cancel(t_con1);
    mu_check(p_sum >= 2);
    mu_check(c_sum >= 2);
}

MU_TEST_SUITE(bq) {
	MU_RUN_TEST(bq_index);
}
/* blocked_queue.c test suite end */

int main(int argc, char *argv[]) {
    printf("Run test suite for 'blocked_queue.c':\n");
    MU_RUN_SUITE(bq);

	MU_REPORT();
	return MU_EXIT_CODE;
}

