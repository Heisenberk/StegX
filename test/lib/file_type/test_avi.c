/* Inclusions minimales. */
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

/* Inclusions supplémentaires. */
#include <errno.h>
#include <unistd.h>
#include "stegx.h"
#include "common.h"

/**
 * Teste la vérification du format AVI.
 * */

void test_file_avi_v1(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/flv/test13.flv", "r");
    assert_non_null(f);
    assert_int_equal(stegx_test_file_avi(f), UNKNOWN);
    fclose(f);
}

void test_file_avi_v2(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/avi/test14.avi", "r");
    assert_non_null(f);
    assert_int_equal(stegx_test_file_avi(f), AVI_UNCOMPRESSED);
    fclose(f);

}

int main(void)
{
    /* Structure CMocka contenant la liste des tests. */
    const struct CMUnitTest check_compatibility_tests[] = {
        cmocka_unit_test(test_file_avi_v1),
        cmocka_unit_test(test_file_avi_v2)
    };

    /* Exécute les tests. */
    return cmocka_run_group_tests(check_compatibility_tests, NULL, NULL);
}
