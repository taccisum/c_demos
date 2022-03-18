/* avoid conflicted function main definitions */
#define __ut

/* unit test framework */
#include "../lib/minunit.h"

/* bin_oper.c test suite start */
#include "../bin_oper/main.c"

MU_TEST(bo_bin_to_dec_check) {
	mu_check(bin_to_dec("000000") == 0);
	mu_check(bin_to_dec("001100") == 12);
	mu_check(bin_to_dec("101100") == 44);
	mu_check(bin_to_dec("111111") == 63);
}

MU_TEST(bo_itob_check) {
    char bs[7];
    itob(0, bs, 6);
	mu_check(strcmp(bs, "000000") == 0);
    itob(12, bs, 6);
	mu_check(strcmp(bs, "001100") == 0);
    itob(44, bs, 6);
	mu_check(strcmp(bs, "101100") == 0);
    itob(63, bs, 6);
	mu_check(strcmp(bs, "111111") == 0);
}

MU_TEST(bo_to_oc_check) {
    char oc[7];
    to_oc("000000", oc, 6);
	mu_check(strcmp(oc, "111111") == 0);
    to_oc("001100", oc, 6);
	mu_check(strcmp(oc, "110011") == 0);
    to_oc("101100", oc, 6);
	mu_check(strcmp(oc, "010011") == 0);
    to_oc("111111", oc, 6);
	mu_check(strcmp(oc, "000000") == 0);
}

MU_TEST(bo_to_tc_check) {
    char tc[7];
    to_tc("000000", tc, 6);
	mu_check(strcmp(tc, "000000") == 0);
    to_tc("001100", tc, 6);
	mu_check(strcmp(tc, "110100") == 0);
    to_tc("101100", tc, 6);
	mu_check(strcmp(tc, "010100") == 0);
    to_tc("111111", tc, 6);
	mu_check(strcmp(tc, "000001") == 0);
}

MU_TEST_SUITE(bin_oper) {
	MU_RUN_TEST(bo_bin_to_dec_check);
	MU_RUN_TEST(bo_itob_check);
	MU_RUN_TEST(bo_to_oc_check);
	MU_RUN_TEST(bo_to_tc_check);
}
/* bin_oper.c test suite end */

int main(int argc, char *argv[]) {
    printf("Run test suite for 'bin_oper.c':\n");
    MU_RUN_SUITE(bin_oper);
	MU_REPORT();
	return MU_EXIT_CODE;
}

