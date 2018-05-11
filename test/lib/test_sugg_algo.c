/* Inclusions minimales. */
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

/* Inclusions supplémentaires. */
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "stegx.h"
#include "common.h"

#define LENGTH_DEFAULT_PASSWD 64


/* Setup des tests unitaires pour les formats de fichiers */
static int test_file_info__setup(void **state)
{
    info_s *infos = malloc(sizeof(info_s));
    assert_non_null(infos);
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->res = fopen("res.bmp", "w"), assert_non_null(infos->res);
    infos->hidden_name =
        malloc((strlen("test16.txt") + 1) * sizeof(char)), assert_non_null(infos->hidden_name);
    strcpy(infos->hidden_name, "test16.txt");
    infos->hidden = fopen("../../../env/test/test16.txt", "r"), assert_non_null(infos->hidden);
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char)), assert_non_null(infos->passwd);
    strcpy(infos->passwd, "stegx");
    stegx_propos_algos =
        malloc(STEGX_NB_ALGO * sizeof(algo_e)), assert_non_null(stegx_propos_algos);
    *state = infos;
    return 0;
}

/* Teardown des tests unitaires pour les formats de fichiers */
static int test_file_info__teardown(void **state)
{
    info_s *infos = *state;
    fclose(infos->res);
    fclose(infos->hidden);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);
    return 0;
}

/**
 * Tests BMP
 * ===================================================================================
 * */

void test_file_info_bmp_v1(void **state)
{
    info_s *infos = *state;
	infos->host.host = fopen("../../../env/test/test1.bmp", "r"), 
					assert_non_null(infos->host.host);
    infos->host.type = BMP_COMPRESSED;
    
    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
	//HEADER SIZE
	assert_int_equal(infos->host.file_info.bmp.header_size, 138);
	//DATA SIZE
	assert_int_equal(infos->host.file_info.bmp.data_size, 14056960);
	//PIXEL LENGTH
	assert_int_equal(infos->host.file_info.bmp.pixel_length, 16);
	//NUMBER OF PIXELS = (pixel width (2584) * pixel height (2720))
	assert_int_equal(infos->host.file_info.bmp.pixel_number, 7028480);

	fclose(infos->host.host);
}

void test_file_info_bmp_v2(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test4.bmp", "r");
    infos->host.type = BMP_UNCOMPRESSED;
    
    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
	//HEADER SIZE
	assert_int_equal(infos->host.file_info.bmp.header_size, 122);
	//DATA SIZE
	assert_int_equal(infos->host.file_info.bmp.data_size, 21085440);
	//PIXEL LENGTH
	assert_int_equal(infos->host.file_info.bmp.pixel_length, 24);
	//NUMBER OF PIXELS = (pixel width (2584) * pixel height (2720))
	assert_int_equal(infos->host.file_info.bmp.pixel_number, 7028480);

	fclose(infos->host.host);
}

void test_file_info_bmp_v3(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test6.bmp", "r");
    infos->host.type = BMP_COMPRESSED;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
	//HEADER SIZE
	assert_int_equal(infos->host.file_info.bmp.header_size, 138);
	//DATA SIZE
	assert_int_equal(infos->host.file_info.bmp.data_size, 28113920);
	//PIXEL LENGTH
	assert_int_equal(infos->host.file_info.bmp.pixel_length, 32);
	//NUMBER OF PIXELS = (pixel width (2584) * pixel height (2720))
	assert_int_equal(infos->host.file_info.bmp.pixel_number, 7028480);

	fclose(infos->host.host);
}

/**
 * Tests PNG
 * =========================================================================================
 * */

void test_file_info_png_v1(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test8.png", "r");
    infos->host.type = PNG;

     /* Valeurs à trouver: */
    stegx_suggest_algo(infos);
    //HEADER SIZE
	assert_int_equal(infos->host.file_info.png.header_size, 21);
	//DATA SIZE
	assert_int_equal(infos->host.file_info.png.data_size, 139005);
	
    fclose(infos->host.host);
}

void test_file_info_png_v2(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test9.png", "r"),
			assert_non_null(infos->host.host);
    infos->host.type = PNG;
    
    /* Valeurs à trouver: */
    stegx_suggest_algo(infos);
    //HEADER SIZE
	assert_int_equal(infos->host.file_info.png.header_size, 21);
	//DATA SIZE
	assert_int_equal(infos->host.file_info.png.data_size, 20525);
	
    fclose(infos->host.host);
}

/**
 * Tests FLV
 * =================================================================================
 * */

/* Test sur un fichier FLV basic */
void test_file_info_flv_v1(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test13.flv", "r"), 
				assert_non_null(infos->host.host);
    infos->host.type = FLV;

	/* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // NOMBRE DE VIDEO TAG :
    assert_int_equal(infos->host.file_info.flv.nb_video_tag, 108);
    // NOMBRE DE METADATA TAG :
    assert_int_equal(infos->host.file_info.flv.nb_metadata_tag, 1);
    // TOTAL SIZE
    assert_int_equal(infos->host.file_info.flv.file_size, 203258);
	
	fclose(infos->host.host);
}

/* Test sur un fichier FLV avec des données écrite après l'end of file */
void test_file_info_flv_v2(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test17.flv", "r"), 
				assert_non_null(infos->host.host);
    infos->host.type = FLV;

	/* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // NOMBRE DE VIDEO TAG :
    assert_int_equal(infos->host.file_info.flv.nb_video_tag, 2);
    // NOMBRE DE METADATA TAG :
    assert_int_equal(infos->host.file_info.flv.nb_metadata_tag, 1);
    // TOTAL SIZE
    assert_int_equal(infos->host.file_info.flv.file_size, 88722);
	
	fclose(infos->host.host);
}

/**
 * Tests WAVE
 * =============================================================================
 */

static void test_file_info_wav__pcm_alaw_1(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_1.wav", "r"),
        assert_non_null(infos->host.host);
    infos->host.type = WAV_NO_PCM;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // CHUNK SIZE :
    assert_int_equal(infos->host.file_info.wav.chunk_size, 8);
    // HEADER SIZE :
    assert_int_equal(infos->host.file_info.wav.header_size, 56);
    // DATA SIZE :
    assert_int_equal(infos->host.file_info.wav.data_size, 106408);
    // TOTAL SIZE : 106464

    fclose(infos->host.host);
}

static void test_file_info_wav__pcm_alaw_2(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav", "r"),
        assert_non_null(infos->host.host);
    infos->host.type = WAV_NO_PCM;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // CHUNK SIZE :
    assert_int_equal(infos->host.file_info.wav.chunk_size, 8);
    // HEADER SIZE :
    assert_int_equal(infos->host.file_info.wav.header_size, 56);
    // DATA SIZE :
    assert_int_equal(infos->host.file_info.wav.data_size, 160580);
    // TOTAL SIZE : 160636

    fclose(infos->host.host);
}

static void test_file_info_wav__pcm_s16le(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/wave/WAVE_PCM(S16_LE)_Mono_44,1kHz_16bits.wav", "r"),
        assert_non_null(infos->host.host);
    infos->host.type = WAV_NO_PCM;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // CHUNK SIZE :
    assert_int_equal(infos->host.file_info.wav.chunk_size, 16);
    // HEADER SIZE :
    assert_int_equal(infos->host.file_info.wav.header_size, 78);
    // DATA SIZE :
    assert_int_equal(infos->host.file_info.wav.data_size, 34230272);
    // TOTAL SIZE : 34230350

    fclose(infos->host.host);
}

/**
 * Tests généraux
 * =============================================================================
 */

/* Setup des tests unitaires pour les propositions d'algos */
static int test_propos_algos__setup(void **state)
{
    info_s *infos = malloc(sizeof(info_s));
    assert_non_null(infos);
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->res = fopen("res.bmp", "w"), assert_non_null(infos->res);
    infos->hidden_name =
        malloc((strlen("hide.txt") + 1) * sizeof(char)), assert_non_null(infos->hidden_name);
    strcpy(infos->hidden_name, "hide.txt");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char)), assert_non_null(infos->passwd);
    strcpy(infos->passwd, "stegx");
    stegx_propos_algos =
        malloc(STEGX_NB_ALGO * sizeof(algo_e)), assert_non_null(stegx_propos_algos);
    *state = infos;
    return 0;
}

/* Teardown des tests unitaires pour les propositions d'algos */
static int test_propos_algos__teardown(void **state)
{
    info_s *infos = *state;
    fclose(infos->res);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);
    return 0;
}

/* Test vérifiant la taille du fichier à cacher */
void test_hidden_length(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test1.bmp", "r"),
				assert_non_null(infos->host.host);
    infos->host.type = BMP_COMPRESSED;
    infos->hidden = fopen("../../../env/test/test2.bmp", "r"),
				assert_non_null(infos->hidden);
    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    assert_int_equal(infos->hidden_length, 14057098);

	fclose(infos->host.host);
	fclose(infos->hidden);
}

/**
 * Tests proposition des algos
 * ==================================================================================
 * */

/* Test sur BMP compressé. 
 * Le fichier à cacher est trop gros pour pouvoir proposer l'algorithme lsb
 * */
void test_propos_algos_v1(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test1.bmp", "r"),
				assert_non_null(infos->host.host);
    infos->hidden = fopen("../../../env/test/wave/WAVE_PCM(S16_LE)_Mono_44,1kHz_16bits.wav", "r"),
				assert_non_null(infos->hidden);
    infos->host.type = BMP_COMPRESSED;
    
    /* Valeurs à trouver */
    stegx_suggest_algo(infos);
    //LSB
    assert_int_equal(stegx_propos_algos[0], 0);
    //EOF
    assert_int_equal(stegx_propos_algos[1], 1);
    //METADATA
    assert_int_equal(stegx_propos_algos[2], 1);
    //EOC : end of chunk
    assert_int_equal(stegx_propos_algos[3], 0);
    //JUNK_CHUNK
    assert_int_equal(stegx_propos_algos[4], 0);
	
	fclose(infos->host.host);
	fclose(infos->hidden);
}

/* Test sur BMP non compressé */
void test_propos_algos_v2(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test4.bmp", "r"),
				assert_non_null(infos->host.host);
    infos->hidden = fopen("../../../env/test/test16.txt", "r"), 
				assert_non_null(infos->hidden);
    infos->host.type = BMP_UNCOMPRESSED;
    
    /* Valeurs à trouver */
    stegx_suggest_algo(infos);
    //LSB
    assert_int_equal(stegx_propos_algos[0], 1);
    //EOF
    assert_int_equal(stegx_propos_algos[1], 1);
    //METADATA
    assert_int_equal(stegx_propos_algos[2], 1);
    //EOC : end of chunk
    assert_int_equal(stegx_propos_algos[3], 0);
    //JUNK_CHUNK
    assert_int_equal(stegx_propos_algos[4], 0);
    
    fclose(infos->host.host);
    fclose(infos->hidden);
}

/* Test sur FLV */
void test_propos_algos_v3(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test13.flv", "r"),
				assert_non_null(infos->host.host);
    infos->hidden = fopen("../../../env/test/test16.txt", "r"),
				assert_non_null(infos->hidden);
    infos->host.type = FLV;
 
    /* Valeurs à trouver */
    stegx_suggest_algo(infos);
    //LSB
    assert_int_equal(stegx_propos_algos[0], 0);
    //EOF
    assert_int_equal(stegx_propos_algos[1], 1);
    //METADATA
    assert_int_equal(stegx_propos_algos[2], 1);
    //EOC : end of chunk
    assert_int_equal(stegx_propos_algos[3], 1);
    //JUNK_CHUNK
    assert_int_equal(stegx_propos_algos[4], 0);
    
    fclose(infos->host.host);
    fclose(infos->hidden);
}

/* Test sur l'AVI non compressé */
void test_propos_algos_v4(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/test14.avi", "r"),
				assert_non_null(infos->host.host);
    infos->hidden = fopen("../../../env/test/test16.txt", "r"),
				assert_non_null(infos->hidden);
    infos->host.type = AVI_UNCOMPRESSED;

    /* Valeurs à trouver */
    stegx_suggest_algo(infos);
    //LSB
    assert_int_equal(stegx_propos_algos[0], 0);
    //EOF
    assert_int_equal(stegx_propos_algos[1], 0);
    //METADATA
    assert_int_equal(stegx_propos_algos[2], 1);
    //EOC : end of chunk
    assert_int_equal(stegx_propos_algos[3], 0);
    //JUNK_CHUNK
    assert_int_equal(stegx_propos_algos[4], 1);
    
    fclose(infos->host.host);
    fclose(infos->hidden);
}

/* Test la taille par défaut du mot de passe lorsque la méthode sans
 * mot de passe a été choisit par l'utilisateur. */
void test_passwd_default_length(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->method = STEGX_WITHOUT_PASSWD;
    infos->host.host = fopen("../../../env/test/test14.avi", "r"),
				assert_non_null(infos->host.host);
    infos->host.type = AVI_UNCOMPRESSED;
    infos->res = fopen("res.bmp", "w"),
				assert_non_null(infos->res);
    infos->hidden_name = malloc((strlen("test16.txt") + 1) * sizeof(char)),
				assert_non_null(infos->hidden_name);
    strcpy(infos->hidden_name, "test16.txt");
    infos->hidden = fopen("../../../env/test/test16.txt", "r"),
				assert_non_null(infos->host.host);
    infos->passwd = NULL;
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e)),
				assert_non_null(stegx_propos_algos);

    stegx_suggest_algo(infos);
    stegx_choose_algo(infos, STEGX_ALGO_EOF);

    int length_passwd_default = strlen(infos->passwd);

    fclose(infos->host.host);
    fclose(infos->res);
    fclose(infos->hidden);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);

    assert_int_equal(length_passwd_default, LENGTH_DEFAULT_PASSWD);
}

/**
 * Main
 * =============================================================================
 */

int main(void)
{
    /* Liste des tests généraux. */
    const struct CMUnitTest propos_algos_tests[] = {
        cmocka_unit_test(test_hidden_length),
        cmocka_unit_test(test_propos_algos_v1),
        cmocka_unit_test(test_propos_algos_v2),
        cmocka_unit_test(test_propos_algos_v3),
        cmocka_unit_test(test_propos_algos_v4)
    };

    /* Liste des tests de chaque format. */
    const struct CMUnitTest sugg_algos_tests_format[] = {
        //liste des tests pour BMP
        cmocka_unit_test(test_file_info_bmp_v1),
        cmocka_unit_test(test_file_info_bmp_v2),
        cmocka_unit_test(test_file_info_bmp_v3),
        //Liste des tests pour le PNG
        cmocka_unit_test(test_file_info_png_v1),
        cmocka_unit_test(test_file_info_png_v2),
        //Liste des tests pour le WAV
        cmocka_unit_test(test_file_info_wav__pcm_alaw_1),
        cmocka_unit_test(test_file_info_wav__pcm_alaw_2),
        cmocka_unit_test(test_file_info_wav__pcm_s16le),
        //Liste des tests pour le FLV
        cmocka_unit_test(test_file_info_flv_v1),
        cmocka_unit_test(test_file_info_flv_v2)
    };

    /* Exécute les tests. */

    int failed_tests;
    /* Si failed_tests est positif, on stop et on le renvoie. Sinon, on fait tout les tests. */
    if ((failed_tests = cmocka_run_group_tests(sugg_algos_tests_format, test_file_info__setup, test_file_info__teardown))) {}
    else if ((failed_tests = cmocka_run_group_tests(propos_algos_tests, test_propos_algos__setup, test_propos_algos__teardown))) {}
    else if ((failed_tests = run_test(test_passwd_default_length))) {}
    return failed_tests;
}
