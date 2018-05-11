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

void test_file_wav__wave_pcm_alaw_1(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_1.wav", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_wav(f), WAV_NO_PCM);
    fclose(f);
}

void test_file_wav__wave_pcm_alaw_2(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_wav(f), WAV_NO_PCM);
    fclose(f);
}

void test_file_wav__wave_pcm_s16le(void **state)
{
    (void)state;                /* Unused */
    FILE *f = fopen("../../../env/test/wave/WAVE_PCM(S16_LE)_Mono_44,1kHz_16bits.wav", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_wav(f), WAV_PCM);
    fclose(f);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest wave_tests[] = {
    cmocka_unit_test(test_file_wav__wave_pcm_alaw_1),
    cmocka_unit_test(test_file_wav__wave_pcm_alaw_2),
    cmocka_unit_test(test_file_wav__wave_pcm_s16le)
};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(wave_tests, NULL, NULL);
}
