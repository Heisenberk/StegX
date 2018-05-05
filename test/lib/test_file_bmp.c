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

extern type_e check_file_format(FILE * file);

/* Tests */

void test_file_bmp_v1(void **state)
{
    // 16 bits R5 G6 B5
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test1.bmp", "r");
    type_e test = stegx_test_file_bmp(f);
    if(f!=NULL) fclose(f);
    assert_int_equal(test, BMP_COMPRESSED);
}

void test_file_bmp_v2(void **state)
{
    // 16 bits R5 G6 B5
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test2.bmp", "r");
    type_e test = stegx_test_file_bmp(f);
    if (f != NULL)
        fclose(f);
    assert_int_equal(test, BMP_COMPRESSED);
}

void test_file_bmp_v3(void **state)
{
    // 16 bits R5 G6 B5
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test3.bmp", "r");
    type_e test = stegx_test_file_bmp(f);
    if (f != NULL)
        fclose(f);
    assert_int_equal(test, BMP_COMPRESSED);
}

void test_file_bmp_v4(void **state)
{
    // 24 bits R8 G8 B8
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test4.bmp", "r");
    type_e test = stegx_test_file_bmp(f);
    if (f != NULL)
        fclose(f);
    assert_int_equal(test, BMP_UNCOMPRESSED);
}

void test_file_bmp_v5(void **state)
{
    // 32 bits A8 R8 G8 B8
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test5.bmp", "r");
    type_e test = stegx_test_file_bmp(f);
    if (f != NULL)
        fclose(f);
    assert_int_equal(test, BMP_COMPRESSED);
}

void test_file_bmp_v6(void **state)
{
    // 32 bits X8 R8 G8 B8
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test6.bmp", "r");
    type_e test = stegx_test_file_bmp(f);
    if (f != NULL)
        fclose(f);
    assert_int_equal(test, BMP_COMPRESSED);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest check_compatibility_tests[] = {

    // tests unitaires BMP
    cmocka_unit_test(test_file_bmp_v1),
    cmocka_unit_test(test_file_bmp_v2),
    cmocka_unit_test(test_file_bmp_v3),
    cmocka_unit_test(test_file_bmp_v4),
    cmocka_unit_test(test_file_bmp_v5),
    cmocka_unit_test(test_file_bmp_v6),

};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(check_compatibility_tests, NULL, NULL);
}
