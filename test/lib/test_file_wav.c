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

void test_file_wav_v1(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/inexistant", "r");
    type_e test = stegx_test_file_wav(f);
    if (f != NULL)
        fclose(f);
    assert_int_equal(test, UNKNOWN);
}

void test_file_wav_v2(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test10.wav", "r");
    type_e test = stegx_test_file_wav(f);
    if (f != NULL)
        fclose(f);
    assert_int_equal(test, WAV_NO_PCM);
}

void test_file_wav_v3(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test11.wav", "r");
    type_e test = stegx_test_file_wav(f);
    if (f != NULL)
        fclose(f);
    assert_int_equal(test, WAV_NO_PCM);
}

void test_file_wav_v4(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/test15.wav", "r");
    type_e test = stegx_test_file_wav(f);
    if (f != NULL)
        fclose(f);
    assert_int_equal(test, WAV_PCM);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest check_compatibility_tests[] = {

    // tests unitaires WAV
    cmocka_unit_test(test_file_wav_v1),
    cmocka_unit_test(test_file_wav_v2),
    cmocka_unit_test(test_file_wav_v3),
    cmocka_unit_test(test_file_wav_v4),

};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(check_compatibility_tests, NULL, NULL);
}
