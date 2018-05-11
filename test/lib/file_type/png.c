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
 * Teste la vérification du format MP3.
 * */
 
void test_file_png_v1(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test8.png", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_png(f), PNG);
    fclose(f);
}

void test_file_png_v2(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test9.png", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_png(f), PNG);
    fclose(f);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest check_compatibility_tests[] = {

    // tests unitaires PNG
    cmocka_unit_test(test_file_png_v1),
    cmocka_unit_test(test_file_png_v2)
};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(check_compatibility_tests, NULL, NULL);
}
