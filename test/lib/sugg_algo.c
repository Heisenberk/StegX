/* Inclusions minimales. */
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

/* Inclusions supplémentaires. */
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "stegx.h"
#include "common.h"

#define ALGO_UNAVAILABLE -1

#define LENGTH_DEFAULT_PASSWD  64

/* Tests */

void test_hidden_length(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test1.bmp", "r");
    infos->host.type = BMP_COMPRESSED;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);
    uint32_t hidden_length = infos->hidden_length;

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    int test;
    test = (hidden_length == 14057098);
    assert_int_equal(test, 1);
}

void test_file_info_bmp_v1(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test1.bmp", "r");
    infos->host.type = BMP_COMPRESSED;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);
    uint32_t header_size = infos->host.file_info.bmp.header_size;
    uint32_t data_size = infos->host.file_info.bmp.data_size;
    uint32_t pixel_length = infos->host.file_info.bmp.pixel_length;
    uint32_t pixel_number = infos->host.file_info.bmp.pixel_number;

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    /*
       Valeurs à trouver:
       HEADER SIZE: 138 octets 
       DATA SIZE: 14056960 octets 
       EVERYTHING: 14057098 octets
       PIXEL LENGTH:16 bits
       PIXEL WIDTH:2584
       PIXEL HEIGHT:2720
     */

    int test;
    test = ((header_size == 138) && (data_size == 14056960) && (pixel_length == 16)
            && (pixel_number == 2584 * 2720));
    assert_int_equal(test, 1);
}

void test_file_info_bmp_v2(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test4.bmp", "r");
    infos->host.type = BMP_UNCOMPRESSED;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);
    uint32_t header_size = infos->host.file_info.bmp.header_size;
    uint32_t data_size = infos->host.file_info.bmp.data_size;
    uint32_t pixel_length = infos->host.file_info.bmp.pixel_length;
    uint32_t pixel_number = infos->host.file_info.bmp.pixel_number;

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    /*
       Valeurs à trouver:
       HEADER SIZE: 122 octets 
       DATA SIZE: 21085440 octets 
       EVERYTHING: 21085562 octets
       PIXEL LENGTH:24 bits
       PIXEL WIDTH:2584
       PIXEL HEIGHT:2720
     */

    int test;
    test = ((header_size == 122) && (data_size == 21085440) && (pixel_length == 24)
            && (pixel_number == 2584 * 2720));
    assert_int_equal(test, 1);
}

void test_file_info_bmp_v3(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test6.bmp", "r");
    infos->host.type = BMP_COMPRESSED;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);
    uint32_t header_size = infos->host.file_info.bmp.header_size;
    uint32_t data_size = infos->host.file_info.bmp.data_size;
    uint32_t pixel_length = infos->host.file_info.bmp.pixel_length;
    uint32_t pixel_number = infos->host.file_info.bmp.pixel_number;

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    /*
       Valeurs à trouver:
       HEADER SIZE: 138 octets 
       DATA SIZE: 28113920 octets 
       EVERYTHING: 28114058 octets
       PIXEL LENGTH:32 bits
       PIXEL WIDTH:2584
       PIXEL HEIGHT:2720
     */

    int test;
    test = ((header_size == 138) && (data_size == 28113920) && (pixel_length == 32)
            && (pixel_number == 2584 * 2720));
    assert_int_equal(test, 1);
}

void test_file_info_png_v1(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test8.png", "r");
    infos->host.type = PNG;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);
    uint32_t header_size = infos->host.file_info.png.header_size;
    uint32_t data_size = infos->host.file_info.png.data_size;

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    /*
       Valeurs à trouver:
       LENGTH HEADER: 21
       DATA SIZE:139005
     */

    int test;
    test = ((header_size == 21) && (data_size == 139005));
    assert_int_equal(test, 1);
}

void test_file_info_png_v2(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test9.png", "r");
    infos->host.type = PNG;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);
    uint32_t header_size = infos->host.file_info.png.header_size;
    uint32_t data_size = infos->host.file_info.png.data_size;

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    /*
       Valeurs à trouver:
       LENGTH HEADER: 21
       DATA SIZE:20525
     */

    int test;
    test = ((header_size == 21) && (data_size == 20525));
    assert_int_equal(test, 1);
}

void test_file_info_wav_v1(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test10.wav", "r");
    infos->host.type = WAV_NO_PCM;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);
    uint32_t header_size = infos->host.file_info.wav.header_size;
    uint32_t data_size = infos->host.file_info.wav.data_size;
    uint32_t chunk_size = infos->host.file_info.wav.chunk_size;

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    /*
       Valeurs à trouver:
       HEADER SIZE:48
       DATA SIZE:106416
       CHUNK SIZE:8
     */

    int test;
    test = ((header_size == 48) && (data_size == 106416) && (chunk_size == 8));
    assert_int_equal(test, 1);
}

void test_file_info_wav_v2(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test11.wav", "r");
    infos->host.type = WAV_NO_PCM;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);
    uint32_t header_size = infos->host.file_info.wav.header_size;
    uint32_t data_size = infos->host.file_info.wav.data_size;
    uint32_t chunk_size = infos->host.file_info.wav.chunk_size;

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    /*
       Valeurs à trouver:
       HEADER SIZE:48
       DATA SIZE:160588
       CHUNK SIZE:8
     */

    int test;
    test = ((header_size == 48) && (data_size == 160588) && (chunk_size == 8));
    assert_int_equal(test, 1);
}

void test_file_info_wav_v3(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test15.wav", "r");
    infos->host.type = WAV_PCM;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);
    uint32_t header_size = infos->host.file_info.wav.header_size;
    uint32_t data_size = infos->host.file_info.wav.data_size;
    uint32_t chunk_size = infos->host.file_info.wav.chunk_size;

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    /*
       Valeurs à trouver:
       HEADER SIZE:70
       DATA SIZE:34230280
       CHUNK SIZE:16
     */

    int test;
    test = ((header_size == 70) && (data_size == 34230280) && (chunk_size == 16));
    assert_int_equal(test, 1);
}

void test_file_info_flv_v1(void **state)
{
    (void)state;
    // A REMPLIR
    int test = 1;
    assert_int_equal(test, 1);
}

void test_propos_algos_v1(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test1.bmp", "r");
    infos->host.type = BMP_COMPRESSED;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test15.wav", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);

    // algos eof et metadata proposés
    int test = ((stegx_propos_algos[0] == STEGX_ALGO_EOF)
                && (stegx_propos_algos[1] == ALGO_UNAVAILABLE)
                && (stegx_propos_algos[2] == STEGX_ALGO_METADATA)
                && (stegx_propos_algos[3] == ALGO_UNAVAILABLE)
                && (stegx_propos_algos[4] == ALGO_UNAVAILABLE));

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    assert_int_equal(test, 1);
}

void test_propos_algos_v2(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test4.bmp", "r");
    infos->host.type = BMP_UNCOMPRESSED;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test16.txt") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test16.txt");
    infos->hidden = fopen("../../../env/test/test16.txt", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);

    // algos eof, lsb et metadata proposés
    int test = ((stegx_propos_algos[0] == STEGX_ALGO_EOF)
                && (stegx_propos_algos[1] == STEGX_ALGO_LSB)
                && (stegx_propos_algos[2] == STEGX_ALGO_METADATA)
                && (stegx_propos_algos[3] == ALGO_UNAVAILABLE)
                && (stegx_propos_algos[4] == ALGO_UNAVAILABLE));

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    assert_int_equal(test, 1);
}

void test_propos_algos_v3(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test13.flv", "r");
    infos->host.type = FLV;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test16.txt") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test16.txt");
    infos->hidden = fopen("../../../env/test/test16.txt", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);

    // algos eof, lsb et metadata proposés
    int test = ((stegx_propos_algos[0] == STEGX_ALGO_EOF)
                && (stegx_propos_algos[1] == ALGO_UNAVAILABLE)
                && (stegx_propos_algos[2] == STEGX_ALGO_METADATA)
                && (stegx_propos_algos[3] == STEGX_ALGO_EOC)
                && (stegx_propos_algos[4] == ALGO_UNAVAILABLE));

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    assert_int_equal(test, 1);
}

void test_propos_algos_v4(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test14.avi", "r");
    infos->host.type = AVI_UNCOMPRESSED;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test16.txt") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test16.txt");
    infos->hidden = fopen("../../../env/test/test16.txt", "r");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");

    stegx_suggest_algo(infos);

    // algos eof, lsb et metadata proposés
    int test = ((stegx_propos_algos[0] == STEGX_ALGO_EOF)
                && (stegx_propos_algos[1] == ALGO_UNAVAILABLE)
                && (stegx_propos_algos[2] == STEGX_ALGO_METADATA)
                && (stegx_propos_algos[3] == ALGO_UNAVAILABLE)
                && (stegx_propos_algos[4] == STEGX_ALGO_JUNK_CHUNK));

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    assert_int_equal(test, 1);
}

void test_passwd_default_length(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->method = STEGX_WITHOUT_PASSWD;
    infos->host.host = fopen("../../../env/test/test14.avi", "r");
    infos->host.type = AVI_UNCOMPRESSED;
    infos->res = fopen("res.bmp", "w");
    infos->hidden_name = malloc((strlen("test16.txt") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test16.txt");
    infos->hidden = fopen("../../../env/test/test16.txt", "r");
    infos->passwd = NULL;

    stegx_suggest_algo(infos);
    stegx_choose_algo(infos, STEGX_ALGO_EOF);

    int length_passwd_default = strlen(infos->passwd);

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    if (infos->hidden_name != NULL)
        free(infos->hidden_name);
    if (infos->passwd != NULL)
        free(infos->passwd);
    if (infos != NULL)
        free(infos);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    assert_int_equal(length_passwd_default, LENGTH_DEFAULT_PASSWD);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest sugg_algos_tests[] = {
    cmocka_unit_test(test_hidden_length),
    cmocka_unit_test(test_file_info_bmp_v1),
    cmocka_unit_test(test_file_info_bmp_v2),
    cmocka_unit_test(test_file_info_bmp_v3),
    cmocka_unit_test(test_file_info_png_v1),
    cmocka_unit_test(test_file_info_png_v2),
    cmocka_unit_test(test_file_info_wav_v1),
    cmocka_unit_test(test_file_info_wav_v2),
    cmocka_unit_test(test_file_info_wav_v3),
    cmocka_unit_test(test_file_info_flv_v1),
    cmocka_unit_test(test_propos_algos_v1),
    cmocka_unit_test(test_propos_algos_v2),
    cmocka_unit_test(test_propos_algos_v3),
    cmocka_unit_test(test_propos_algos_v4),
    cmocka_unit_test(test_passwd_default_length),
};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(sugg_algos_tests, NULL, NULL);
}
