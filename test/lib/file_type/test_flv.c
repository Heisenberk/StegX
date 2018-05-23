#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

#include <errno.h>
#include <unistd.h>
#include "stegx.h"
#include "common.h"

/*
 * Teste la vérification du format FLV.
 * */
 
void test_file_flv_v1(void **state)
{
    (void)state;        
    FILE *f = fopen("../../../env/test/bmp/test1.bmp", "r");
    assert_non_null(f);
    assert_int_equal(stegx_test_file_flv(f), UNKNOWN);
    fclose(f);
}

void test_file_flv_v2(void **state)
{
    (void)state;   
    FILE *f = fopen("../../../env/test/flv/test13.flv", "r");
    assert_non_null(f);
    assert_int_equal(stegx_test_file_flv(f), FLV);
    fclose(f);

}

int main(void)
{
    /* Structure CMocka contenant la liste des tests. */
    const struct CMUnitTest flv_tests[] = {
        cmocka_unit_test(test_file_flv_v1),
        cmocka_unit_test(test_file_flv_v2)
    };

    /* Exécute les tests. */
    return cmocka_run_group_tests(flv_tests, NULL, NULL);
}
