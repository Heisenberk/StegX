#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

#include <errno.h>
#include <unistd.h>
#include "stegx.h"
#include "common.h"

/*
 * Teste la vérification du format WAV.
 * */
 
void test_file_wav__wave_pcm_alaw_1(void **state)
{
    (void)state;     
    FILE *f = fopen("../../../env/test/wave/WAVE_PCM(ALAW_16)_Mono_44,1kHz_1.wav", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_wav(f), WAV_NO_PCM);
    fclose(f);
}

void test_file_wav__wave_pcm_alaw_2(void **state)
{
    (void)state;       
    FILE *f = fopen("../../../env/test/wave/WAVE_PCM(ALAW_16)_Mono_44,1kHz_2.wav", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_wav(f), WAV_NO_PCM);
    fclose(f);
}

void test_file_wav__wave_pcm_s16le(void **state)
{
    (void)state;      
    FILE *f = fopen("../../../env/test/wave/WAVE_PCM(S16_LE)_Stereo_44,1kHz.wav", "r");
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
