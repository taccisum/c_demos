/* avoid conflicted function main definitions */
#define __ut

/* unit test framework */
#include "../lib/minunit.h"

/* test suite start */
#include "lexan.c"

int p = 1;
char *_pscan() {
    scan();
    if (p) {
        if(tkv != NULL) {
            printf("[scan] '%s'(%d)\n", tkv, tk);
        }
    }
    return tkv;
}

void ptkv() {
    if (p) {
        printf("[token] '%s'(%d)\n", tkv, tk);
    }
}

MU_TEST(gc_t) {
    init("hello");
    mu_check(gc() == 'h');
    mu_check(gc() == 'e');
    mu_check(gc() == 'l');
    mu_check(gc() == 'l');
    mu_check(gc() == 'o');
    mu_check(gc() == '\0');
}

MU_TEST(take_t) {
    strcpy(buf1, "hello world");
    l = 0, r = 5;
    take(); mu_check(strcmp(tkv, "hello") == 0);
    l = 1, r = 5;
    take(); mu_check(strcmp(tkv, "ello") == 0);
}

MU_TEST(scan_t) {
    init( "hello world");
    scan(); ptkv(); mu_check(strcmp(tkv, "hello") == 0);
    scan(); ptkv(); mu_check(strcmp(tkv, "world") == 0);

    init( "7 * 2+ x0 - 334 / 123");
    scan(); ptkv(); mu_check(strcmp(tkv, "7") == 0);
    scan(); ptkv(); mu_check(strcmp(tkv, "*") == 0);
    scan(); ptkv(); mu_check(strcmp(tkv, "2") == 0);
    scan(); ptkv(); mu_check(strcmp(tkv, "+") == 0);
    scan(); ptkv(); mu_check(strcmp(tkv, "x0") == 0);
    scan(); ptkv(); mu_check(strcmp(tkv, "-") == 0);
    scan(); ptkv(); mu_check(strcmp(tkv, "334") == 0);
    scan(); ptkv(); mu_check(strcmp(tkv, "/") == 0);
    scan(); ptkv(); mu_check(strcmp(tkv, "123") == 0);
}

MU_TEST_SUITE(def) {
	MU_RUN_TEST(gc_t);
	MU_RUN_TEST(take_t);
	MU_RUN_TEST(scan_t);
}
/* blocked_queue.c test suite end */

int main(int argc, char *argv[]) {
    printf("Run test suite for 'lexan.c':\n");
    MU_RUN_SUITE(def);

	MU_REPORT();
	return MU_EXIT_CODE;
}

