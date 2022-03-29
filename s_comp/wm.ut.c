/* avoid conflicted function main definitions */
#define __ut

/* unit test framework */
#include "../lib/minunit.h"

/* test suite start */
#include "with_morph.c"

MU_TEST(lexan_t) {
    str = "123 567 890";
    mu_check(lexan() == 123);
    mu_check(lexan() == 567);
    mu_check(lexan() == 890);
}

#define TK1 1
#define TK2 2
#define TK3 3
MU_TEST(sym_tbl_t) {
    insert(TK1, "tk1");
    insert(TK2, "tk2");
    insert(TK2, "tk2");
    insert(TK3, "tk3");
    mu_check(nava == 4);
    mu_check(lookup("tk1") == TK1);
    mu_check(lookup("tk2") == TK2);
    mu_check(lookup("tk3") == TK3);
}

MU_TEST_SUITE(def) {
	MU_RUN_TEST(lexan_t);
	MU_RUN_TEST(sym_tbl_t);
}
/* blocked_queue.c test suite end */

int main(int argc, char *argv[]) {
    printf("Run test suite for 'with_morph.c':\n");
    MU_RUN_SUITE(def);

	MU_REPORT();
	return MU_EXIT_CODE;
}

