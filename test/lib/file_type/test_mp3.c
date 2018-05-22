#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

#include <errno.h>
#include <unistd.h>
#include "stegx.h"
#include "common.h"

/*
 * Teste la vérification du format MP3.
 * */

void test_file_mp3__wave_pcm_alaw(void **state)
{
    (void)state;        
    FILE *f = fopen("../../../env/test/wave/WAVE_PCM(ALAW_16)_Mono_44,1kHz_1.wav", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_mp3(f), UNKNOWN);
    fclose(f);
}

void test_file_mp3__wave_pcm_s16le(void **state)
{
    (void)state;    
    FILE *f = fopen("../../../env/test/wave/WAVE_PCM(S16_LE)_Stereo_44,1kHz.wav", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_mp3(f), UNKNOWN);
    fclose(f);
}

void test_file_mp3__mp3_mono(void **state)
{
    (void)state;  
    FILE *f = fopen("../../../env/test/mp3/MP3_Mono_44,1kHz_64kbps.mp3", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_mp3(f), MP3);
    fclose(f);
}

void test_file_mp3__mp3_stereo(void **state)
{
    (void)state;     
    FILE *f = fopen("../../../env/test/mp3/MP3_Stereo_44,1kHz_160kbps.mp3", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_mp3(f), MP3);
    fclose(f);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest mp3_tests[] = {
    cmocka_unit_test(test_file_mp3__wave_pcm_alaw),
    cmocka_unit_test(test_file_mp3__wave_pcm_s16le),
    cmocka_unit_test(test_file_mp3__mp3_mono),
    cmocka_unit_test(test_file_mp3__mp3_stereo)
};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(mp3_tests, NULL, NULL);
}
