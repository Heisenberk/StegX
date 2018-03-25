/* Inclusions minimales. */
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

/* Inclusions supplémentaires. */
#include "maths/test.c"

/* Tests */

void test_hello_cli_v2_success(void **state)
{
    (void) state; /* Unused */
    int ret = math1();
    assert_int_equal(0, ret);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest hello_cli_v2_tests[] = {
    cmocka_unit_test(test_hello_cli_v2_success),
};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(hello_cli_v2_tests, NULL, NULL);
}
