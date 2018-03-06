#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

/* Fonction à tester (normalement importée depuis un autre module). */
int do_something(int ret) {
    return ret;
}

/* Tests */

void test_do_something_failure(void **state)
{
    (void) state; /* Unused */
    int ret = do_something(-1);
    assert_int_equal(-1, ret);
}

void test_do_something_success(void **state)
{
    (void) state; /* Unused */
    int ret = do_something(0);
    assert_int_equal(0, ret);
}

/* CMocka. */

const struct CMUnitTest do_something_tests[] = {
    cmocka_unit_test(test_do_something_failure),
    cmocka_unit_test(test_do_something_success),
};

int main(void)
{
    return cmocka_run_group_tests(do_something_tests, NULL, NULL);
}
