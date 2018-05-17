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

#define SIG_RIFF 0x46464952

void dest_stegx_info(stegx_choices_s * com)
{
    if (com->insert_info) {
        free(com->insert_info);
    }
    free(com);

}

/* Test final de l'insertion/extraction EOF sur un fichier BMP avec 
 * mot de passe et un petit fichier a cacher (< a la limite etablie)
 **/
void test_eof_little_bmp_with_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/bmp/test9bis.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/bmp/test9bis.bmp");
    choices_insert->res_path = malloc((strlen("./res1_test_eof.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res1_test_eof.bmp");
    choices_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_insert->passwd, "stegx");
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/others/short.txt") + 1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path, "../../../env/test/others/short.txt");
    choices_insert->insert_info->algo = STEGX_ALGO_EOF;
    int test;

    info_s *infos_insert = stegx_init(choices_insert);

    test = stegx_check_compatibility(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_suggest_algo(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_choose_algo(infos_insert, choices_insert->insert_info->algo);
    assert_int_equal(test, 0);

    test = stegx_insert(infos_insert);
    assert_int_equal(test, 0);

    dest_stegx_info(choices_insert);
    stegx_clear(infos_insert);

    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res1_test_eof.bmp") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res1_test_eof.bmp");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_extract->passwd, "stegx");
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    info_s *infos_extract = stegx_init(choices_extract);

    test = stegx_check_compatibility(infos_extract);
    assert_int_equal(test, 0);

    test = stegx_detect_algo(infos_extract);
    assert_int_equal(test, 0);
    uint32_t length_malloc = infos_extract->hidden_length;
    test = stegx_extract(infos_extract, choices_extract->res_path);
    assert_int_equal(test, 0);

    dest_stegx_info(choices_extract);
    stegx_clear(infos_extract);

    uint8_t c;
    uint32_t i;
    char *message = malloc((length_malloc + 1) * sizeof(char));
    FILE *f = fopen("./short.txt", "r");
    assert_int_equal(f != NULL, 1);
    for (i = 0; i < (length_malloc) - 1; i++) {
        fread(&c, sizeof(uint8_t), 1, f);
        message[i] = c;
    }
    message[length_malloc - 2] = '\0';
    // Test si le contenu du message a bien ete extrait
    test = (strcmp(message, "voici un test tres court.") == 0);
    assert_int_equal(test, 1);
    free(message);
    fclose(f);
    remove("./short.txt");

}

/* Test final de l'insertion/extraction EOF sur un fichier BMP sans 
 * mot de passe et un petit fichier a cacher (< a la limite etablie)
 **/
void test_eof_little_bmp_without_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/bmp/test9bis.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/bmp/test9bis.bmp");
    choices_insert->res_path = malloc((strlen("./res2_test_eof.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res2_test_eof.bmp");
    choices_insert->passwd = NULL;
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/others/short.txt") + 1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path, "../../../env/test/others/short.txt");
    choices_insert->insert_info->algo = STEGX_ALGO_EOF;
    int test;

    info_s *infos_insert = stegx_init(choices_insert);

    test = stegx_check_compatibility(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_suggest_algo(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_choose_algo(infos_insert, choices_insert->insert_info->algo);
    assert_int_equal(test, 0);

    test = stegx_insert(infos_insert);
    assert_int_equal(test, 0);

    stegx_clear(infos_insert);
    dest_stegx_info(choices_insert);

    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res2_test_eof.bmp") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res2_test_eof.bmp");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = NULL;
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    info_s *infos_extract = stegx_init(choices_extract);

    test = stegx_check_compatibility(infos_extract);
    assert_int_equal(test, 0);

    test = stegx_detect_algo(infos_extract);
    assert_int_equal(test, 0);
    uint32_t length_malloc = infos_extract->hidden_length;
    test = stegx_extract(infos_extract, choices_extract->res_path);
    assert_int_equal(test, 0);

    stegx_clear(infos_extract);
    dest_stegx_info(choices_extract);

    uint8_t c;
    uint32_t i;
    char *message = malloc((length_malloc + 1) * sizeof(char));
    FILE *f = fopen("./short.txt", "r");
    assert_int_equal(f != NULL, 1);
    for (i = 0; i < (length_malloc) - 1; i++) {
        fread(&c, sizeof(uint8_t), 1, f);
        message[i] = c;
    }
    message[length_malloc - 2] = '\0';
    // Test si le contenu du message a bien ete extrait
    test = (strcmp(message, "voici un test tres court.") == 0);
    assert_int_equal(test, 1);
    free(message);
    fclose(f);
    remove("./short.txt");
}

/* Test final de l'insertion/extraction EOF sur un fichier PNG avec 
 * mot de passe et un petit fichier a cacher (< a la limite etablie)
 **/
void test_eof_little_png_with_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/png/test8.png") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/png/test8.png");
    choices_insert->res_path = malloc((strlen("./res3_test_eof.png") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res3_test_eof.png");
    choices_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_insert->passwd, "stegx");
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/others/short.txt") + 1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path, "../../../env/test/others/short.txt");
    choices_insert->insert_info->algo = STEGX_ALGO_EOF;
    int test;

    info_s *infos_insert = stegx_init(choices_insert);

    test = stegx_check_compatibility(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_suggest_algo(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_choose_algo(infos_insert, choices_insert->insert_info->algo);
    assert_int_equal(test, 0);

    test = stegx_insert(infos_insert);
    assert_int_equal(test, 0);

    stegx_clear(infos_insert);
    dest_stegx_info(choices_insert);

    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res3_test_eof.png") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res3_test_eof.png");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_extract->passwd, "stegx");
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    info_s *infos_extract = stegx_init(choices_extract);

    test = stegx_check_compatibility(infos_extract);
    assert_int_equal(test, 0);

    test = stegx_detect_algo(infos_extract);
    assert_int_equal(test, 0);
    uint32_t length_malloc = infos_extract->hidden_length;
    test = stegx_extract(infos_extract, choices_extract->res_path);
    assert_int_equal(test, 0);

    stegx_clear(infos_extract);
    dest_stegx_info(choices_extract);

    uint8_t c;
    uint32_t i;
    char *message = malloc((length_malloc + 1) * sizeof(char));
    FILE *f = fopen("./short.txt", "r");
    assert_int_equal(f != NULL, 1);
    for (i = 0; i < (length_malloc) - 1; i++) {
        fread(&c, sizeof(uint8_t), 1, f);
        message[i] = c;
    }
    message[length_malloc - 2] = '\0';
    // Test si le contenu du message a bien ete extrait
    test = (strcmp(message, "voici un test tres court.") == 0);
    assert_int_equal(test, 1);
    free(message);
    fclose(f);
    remove("./short.txt");

}

/* Test final de l'insertion/extraction EOF sur un fichier PNG sans 
 * mot de passe et un petit fichier a cacher (< a la limite etablie)
 **/
void test_eof_little_png_without_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/png/test8.png") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/png/test8.png");
    choices_insert->res_path = malloc((strlen("./res4_test_eof.png") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res4_test_eof.png");
    choices_insert->passwd = NULL;
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/others/short.txt") + 1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path, "../../../env/test/others/short.txt");
    choices_insert->insert_info->algo = STEGX_ALGO_EOF;
    int test;

    info_s *infos_insert = stegx_init(choices_insert);

    test = stegx_check_compatibility(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_suggest_algo(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_choose_algo(infos_insert, choices_insert->insert_info->algo);
    assert_int_equal(test, 0);

    test = stegx_insert(infos_insert);
    assert_int_equal(test, 0);

    stegx_clear(infos_insert);
    dest_stegx_info(choices_insert);

    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res4_test_eof.png") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res4_test_eof.png");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = NULL;
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    info_s *infos_extract = stegx_init(choices_extract);

    test = stegx_check_compatibility(infos_extract);
    assert_int_equal(test, 0);

    test = stegx_detect_algo(infos_extract);
    assert_int_equal(test, 0);
    uint32_t length_malloc = infos_extract->hidden_length;
    test = stegx_extract(infos_extract, choices_extract->res_path);
    assert_int_equal(test, 0);

    stegx_clear(infos_extract);
    dest_stegx_info(choices_extract);

    uint8_t c;
    uint32_t i;
    char *message = malloc((length_malloc + 1) * sizeof(char));
    FILE *f = fopen("./short.txt", "r");
    assert_int_equal(f != NULL, 1);
    for (i = 0; i < (length_malloc) - 1; i++) {
        fread(&c, sizeof(uint8_t), 1, f);
        message[i] = c;
    }
    message[length_malloc - 2] = '\0';
    // Test si le contenu du message a bien ete extrait
    test = (strcmp(message, "voici un test tres court.") == 0);
    assert_int_equal(test, 1);
    free(message);
    fclose(f);
    remove("./short.txt");
}

/* Test final de l'insertion/extraction EOF sur un fichier BMP avec 
 * mot de passe et un gros fichier a cacher (> a la limite etablie)
 **/
void test_eof_big_bmp_with_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/bmp/test9bis.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/bmp/test9bis.bmp");
    choices_insert->res_path = malloc((strlen("./res1_test_eof.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res1_test_eof.bmp");
    choices_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_insert->passwd, "stegx");
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    // fichier de taille superieure a la limite etablie
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav") +
                1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path,
           "../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav");
    choices_insert->insert_info->algo = STEGX_ALGO_EOF;
    int test;

    info_s *infos_insert = stegx_init(choices_insert);

    test = stegx_check_compatibility(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_suggest_algo(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_choose_algo(infos_insert, choices_insert->insert_info->algo);
    assert_int_equal(test, 0);

    test = stegx_insert(infos_insert);
    assert_int_equal(test, 0);

    dest_stegx_info(choices_insert);
    stegx_clear(infos_insert);

    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res1_test_eof.bmp") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res1_test_eof.bmp");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_extract->passwd, "stegx");
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    info_s *infos_extract = stegx_init(choices_extract);

    test = stegx_check_compatibility(infos_extract);
    assert_int_equal(test, 0);

    test = stegx_detect_algo(infos_extract);
    assert_int_equal(test, 0);
    test = stegx_extract(infos_extract, choices_extract->res_path);
    assert_int_equal(test, 0);

    stegx_clear(infos_extract);
    dest_stegx_info(choices_extract);

    FILE *f = fopen("./WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav", "r");
    assert_int_equal(f != NULL, 1);

    // Test si le contenu du message a bien ete extrait*/
    uint32_t sig;
    assert_int_equal(fread(&sig, sizeof(uint32_t), 1, f), 1);
    assert_int_equal((sig == SIG_RIFF), 1);
    fclose(f);
    remove("./WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav");

}

/* Test final de l'insertion/extraction EOF sur un fichier BMP sans 
 * mot de passe et un gros fichier a cacher (> a la limite etablie)
 **/
void test_eof_big_bmp_without_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/bmp/test9bis.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/bmp/test9bis.bmp");
    choices_insert->res_path = malloc((strlen("./res2_test_eof.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res2_test_eof.bmp");
    choices_insert->passwd = NULL;
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav") +
                1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path,
           "../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav");
    choices_insert->insert_info->algo = STEGX_ALGO_EOF;
    int test;

    info_s *infos_insert = stegx_init(choices_insert);

    test = stegx_check_compatibility(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_suggest_algo(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_choose_algo(infos_insert, choices_insert->insert_info->algo);
    assert_int_equal(test, 0);

    test = stegx_insert(infos_insert);
    assert_int_equal(test, 0);

    stegx_clear(infos_insert);
    dest_stegx_info(choices_insert);

    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res2_test_eof.bmp") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res2_test_eof.bmp");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = NULL;
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    info_s *infos_extract = stegx_init(choices_extract);

    test = stegx_check_compatibility(infos_extract);
    assert_int_equal(test, 0);

    test = stegx_detect_algo(infos_extract);
    assert_int_equal(test, 0);
    test = stegx_extract(infos_extract, choices_extract->res_path);
    assert_int_equal(test, 0);

    stegx_clear(infos_extract);
    dest_stegx_info(choices_extract);

    FILE *f = fopen("./WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav", "r");
    assert_int_equal(f != NULL, 1);

    // Test si le contenu du message a bien ete extrait*/
    uint32_t sig;
    assert_int_equal(fread(&sig, sizeof(uint32_t), 1, f), 1);
    assert_int_equal((sig == SIG_RIFF), 1);
    fclose(f);
    remove("./WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav");
}

/* Test final de l'insertion/extraction EOF sur un fichier PNG avec 
 * mot de passe et un gros fichier a cacher (> a la limite etablie)
 **/
void test_eof_big_png_with_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/png/test8.png") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/png/test8.png");
    choices_insert->res_path = malloc((strlen("./res3_test_eof.png") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res3_test_eof.png");
    choices_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_insert->passwd, "stegx");
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav") +
                1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path,
           "../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav");
    choices_insert->insert_info->algo = STEGX_ALGO_EOF;
    int test;

    info_s *infos_insert = stegx_init(choices_insert);

    test = stegx_check_compatibility(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_suggest_algo(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_choose_algo(infos_insert, choices_insert->insert_info->algo);
    assert_int_equal(test, 0);

    test = stegx_insert(infos_insert);
    assert_int_equal(test, 0);

    stegx_clear(infos_insert);
    dest_stegx_info(choices_insert);

    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res3_test_eof.png") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res3_test_eof.png");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_extract->passwd, "stegx");
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    info_s *infos_extract = stegx_init(choices_extract);

    test = stegx_check_compatibility(infos_extract);
    assert_int_equal(test, 0);

    test = stegx_detect_algo(infos_extract);
    assert_int_equal(test, 0);
    test = stegx_extract(infos_extract, choices_extract->res_path);
    assert_int_equal(test, 0);

    stegx_clear(infos_extract);
    dest_stegx_info(choices_extract);

    FILE *f = fopen("./WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav", "r");
    assert_int_equal(f != NULL, 1);

    // Test si le contenu du message a bien ete extrait*/
    uint32_t sig;
    assert_int_equal(fread(&sig, sizeof(uint32_t), 1, f), 1);
    assert_int_equal((sig == SIG_RIFF), 1);
    fclose(f);
    remove("./WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav");

}

/* Test final de l'insertion/extraction EOF sur un fichier PNG sans 
 * mot de passe et un gros fichier a cacher (> a la limite etablie)
 **/
void test_eof_big_png_without_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/png/test8.png") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/png/test8.png");
    choices_insert->res_path = malloc((strlen("./res4_test_eof.png") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res4_test_eof.png");
    choices_insert->passwd = NULL;
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav") +
                1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path,
           "../../../env/test/wave/WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav");
    choices_insert->insert_info->algo = STEGX_ALGO_EOF;
    int test;

    info_s *infos_insert = stegx_init(choices_insert);

    test = stegx_check_compatibility(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_suggest_algo(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_choose_algo(infos_insert, choices_insert->insert_info->algo);
    assert_int_equal(test, 0);

    test = stegx_insert(infos_insert);
    assert_int_equal(test, 0);

    stegx_clear(infos_insert);
    dest_stegx_info(choices_insert);

    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res4_test_eof.png") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res4_test_eof.png");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = NULL;
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    info_s *infos_extract = stegx_init(choices_extract);

    test = stegx_check_compatibility(infos_extract);
    assert_int_equal(test, 0);

    test = stegx_detect_algo(infos_extract);
    assert_int_equal(test, 0);
    test = stegx_extract(infos_extract, choices_extract->res_path);
    assert_int_equal(test, 0);

    stegx_clear(infos_extract);
    dest_stegx_info(choices_extract);

    FILE *f = fopen("./WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav", "r");
    assert_int_equal(f != NULL, 1);

    // Test si le contenu du message a bien ete extrait*/
    uint32_t sig;
    assert_int_equal(fread(&sig, sizeof(uint32_t), 1, f), 1);
    assert_int_equal((sig == SIG_RIFF), 1);
    fclose(f);
    remove("./WAVE_PCM(ALAW)_Mono_44,1kHz_16bits_2.wav");
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest eof_tests[] = {
    cmocka_unit_test(test_eof_little_bmp_with_passwd),
    cmocka_unit_test(test_eof_little_bmp_without_passwd),
    cmocka_unit_test(test_eof_little_png_with_passwd),
    cmocka_unit_test(test_eof_little_png_without_passwd),

    cmocka_unit_test(test_eof_big_bmp_with_passwd),
    cmocka_unit_test(test_eof_big_bmp_without_passwd),
    cmocka_unit_test(test_eof_big_png_with_passwd),
    cmocka_unit_test(test_eof_big_png_without_passwd),
};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(eof_tests, NULL, NULL);
}
