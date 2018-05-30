#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "stegx.h"
#include "common.h"
#include "algo/lsb.h"

#define TEST_DIR "../../../env/test/"

/*
 * Fonction recréée pour libérer la mémoire de la structure stegx_choices_s
 **/
void dest_stegx_info(stegx_choices_s * com)
{
    if (com->insert_info) {
        free(com->insert_info);
    }
    free(com);

}

/* Test final de l'insertion/extraction LSB sur un fichier BMP avec 
 * mot de passe et un petit fichier a cacher (< a la limite etablie)
 **/
void test_lsb_little_bmp_with_passwd(void **state)
{
    (void)state;
    // Initialisation de l'insertion identique aux actions des interfaces
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/bmp/test7.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/bmp/test7.bmp");
    choices_insert->res_path = malloc((strlen("./res1_test_lsb.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res1_test_lsb.bmp");
    choices_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_insert->passwd, "stegx");
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/others/short.txt") + 1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path, "../../../env/test/others/short.txt");
    choices_insert->insert_info->algo = STEGX_ALGO_LSB;
    int test;

    // Insertion 
    info_s *infos_insert = stegx_init(choices_insert);

    test = stegx_check_compatibility(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_suggest_algo(infos_insert);
    assert_int_equal(test, 0);

    test = stegx_choose_algo(infos_insert, choices_insert->insert_info->algo);
    assert_int_equal(test, 0);

    test = stegx_insert(infos_insert);
    assert_int_equal(test, 0);
    uint32_t length_insert = infos_insert->hidden_length;

    stegx_clear(infos_insert);
    dest_stegx_info(choices_insert);

    // Initialisation de l'extraction identique aux actions des interfaces
    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res1_test_lsb.bmp") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res1_test_lsb.bmp");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_extract->passwd, "stegx");
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    //Extraction
    info_s *infos_extract = stegx_init(choices_extract);

    test = stegx_check_compatibility(infos_extract);
    assert_int_equal(test, 0);

    test = stegx_detect_algo(infos_extract);
    assert_int_equal(test, 0);
    uint32_t length_malloc = infos_extract->hidden_length;
    test = stegx_extract(infos_extract, choices_extract->res_path);
    assert_int_equal(test, 0);

    assert_int_equal(length_malloc, length_insert);

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

/* Test final de l'insertion/extraction LSB sur un fichier BMP sans 
 * mot de passe et un petit fichier a cacher (< a la limite etablie)
 **/
void test_lsb_little_bmp_without_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/bmp/test7.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/bmp/test7.bmp");
    choices_insert->res_path = malloc((strlen("./res2_test_lsb.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res2_test_lsb.bmp");
    choices_insert->passwd = NULL;
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/others/short.txt") + 1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path, "../../../env/test/others/short.txt");
    choices_insert->insert_info->algo = STEGX_ALGO_LSB;
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
    strcpy(choices_extract->host_path, "./res2_test_lsb.bmp");
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

/* Test final de l'insertion/extraction LSB sur un fichier BMP avec 
 * mot de passe et un gros fichier hote (> a la limite etablie)
 **/
void test_lsb_big_bmp_with_passwd(void **state)
{
    (void)state;
    // Initialisation de l'insertion identique aux actions des interfaces
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/bmp/test4.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/bmp/test4.bmp");
    choices_insert->res_path = malloc((strlen("./res3_test_lsb.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res3_test_lsb.bmp");
    choices_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_insert->passwd, "stegx");
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/others/short.txt") + 1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path, "../../../env/test/others/short.txt");
    choices_insert->insert_info->algo = STEGX_ALGO_LSB;
    int test;

    // Insertion 
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

    // Initialisation de l'extraction identique aux actions des interfaces
    stegx_choices_s *choices_extract = malloc(sizeof(stegx_choices_s));
    choices_extract->host_path = malloc((strlen("./res3_test_lsb.bmp") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res3_test_lsb.bmp");
    choices_extract->res_path = malloc((strlen("./") + 1) * sizeof(char));
    strcpy(choices_extract->res_path, "./");
    choices_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(choices_extract->passwd, "stegx");
    choices_extract->mode = STEGX_MODE_EXTRACT;
    choices_extract->insert_info = NULL;

    //Extraction
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

/* Test final de l'insertion/extraction LSB sur un fichier BMP sans 
 * mot de passe et un gros fichier hote (> a la limite etablie)
 **/
void test_lsb_big_bmp_without_passwd(void **state)
{
    (void)state;
    stegx_choices_s *choices_insert = malloc(sizeof(stegx_choices_s));
    choices_insert->host_path =
        malloc((strlen("../../../env/test/bmp/test4.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->host_path, "../../../env/test/bmp/test4.bmp");
    choices_insert->res_path = malloc((strlen("./res4_test_lsb.bmp") + 1) * sizeof(char));
    strcpy(choices_insert->res_path, "./res4_test_lsb.bmp");
    choices_insert->passwd = NULL;
    choices_insert->mode = STEGX_MODE_INSERT;
    choices_insert->insert_info = malloc(sizeof(stegx_info_insert_s));
    choices_insert->insert_info->hidden_path =
        malloc((strlen("../../../env/test/others/short.txt") + 1) * sizeof(char));
    strcpy(choices_insert->insert_info->hidden_path, "../../../env/test/others/short.txt");
    choices_insert->insert_info->algo = STEGX_ALGO_LSB;
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
    choices_extract->host_path = malloc((strlen("./res4_test_eof.bmp") + 1) * sizeof(char));
    strcpy(choices_extract->host_path, "./res4_test_lsb.bmp");
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

/* Test d'un LSB sur deux MP3 avec et sans mot de passe. */
void test_lsb_mp3(void **state)
{
    /* Initialisation. */
    (void) state; /* Unused. */
    stegx_choices_s choices_insert, choices_extract;
    stegx_info_insert_s choices_insert_info;
    info_s * infos_insert = NULL, * infos_extract = NULL;
    FILE * fstego = NULL, * forig = NULL;
    FILE * fsrc = NULL, * fdst = NULL;
    uint32_t size = 0, src32 = 0, dst32 = 0;

    /* Fichier en ID3v1 avec mot de passe. */

    /* Initialisation insertion. */
    choices_insert.host_path = TEST_DIR"mp3/MP3_ID3v1_Stereo_44,1kHz_160kbps.mp3";
    choices_insert.res_path = "test_lsb_mp3";
    choices_insert.passwd = "stegx";
    choices_insert.mode = STEGX_MODE_INSERT;
    choices_insert.insert_info = &choices_insert_info;
    choices_insert.insert_info->hidden_path = TEST_DIR"others/short.txt";
    choices_insert.insert_info->algo = STEGX_ALGO_LSB;
    /* Insertion. */
    assert_non_null(infos_insert = stegx_init(&choices_insert));
    assert_false(stegx_check_compatibility(infos_insert));
    assert_false(stegx_suggest_algo(infos_insert));
    assert_false(stegx_choose_algo(infos_insert, choices_insert.insert_info->algo));
    assert_false(stegx_insert(infos_insert));
    stegx_clear(infos_insert);

    /* Vérifie que le fichier stégo n'as pas été altéré. */
    assert_non_null(fstego = fopen("test_lsb_mp3", "rb"));
    assert_non_null(forig = fopen(TEST_DIR"mp3/MP3_ID3v1_Stereo_44,1kHz_160kbps.mp3", "rb"));
    /* On prend quelques échantillons représentatif pour vérifier que le fichier n'as pas été
     * altéré. */
    dst32 = src32 = 0;
    /* Échantillon d'un header MPEG. */
    assert_false(fseek(fstego, 0x20A, SEEK_SET)), assert_false(fseek(forig, 0x20A, SEEK_SET));
    assert_true(fread(&dst32, sizeof(uint16_t), 1, fstego)), assert_true(fread(&src32, sizeof(uint16_t), 1, forig));
    assert_int_equal(dst32, src32);
    /* Échantillon d'une frame MPEG. */
    assert_false(fseek(fstego, 0x100F, SEEK_SET)), assert_false(fseek(forig, 0x100F, SEEK_SET));
    assert_true(fread(&dst32, sizeof(dst32), 1, fstego)), assert_true(fread(&src32, sizeof(dst32), 1, forig));
    assert_int_equal(dst32, src32);
    /* Échantillon d'un tag ID3v1. */
    assert_false(fseek(fstego, 0x3A023, SEEK_SET)), assert_false(fseek(forig, 0x3A023, SEEK_SET));
    assert_true(fread(&dst32, sizeof(dst32), 1, fstego)), assert_true(fread(&src32, sizeof(dst32), 1, forig));
    assert_int_equal(dst32, src32);
    /* Fermeture. */
    assert_false(fclose(fstego)), assert_false(fclose(forig));

    /* Initialisation extraction. */
    choices_extract.host_path = "test_lsb_mp3";
    choices_extract.res_path = "./";
    choices_extract.passwd = "stegx";
    choices_extract.mode = STEGX_MODE_EXTRACT;
    choices_extract.insert_info = NULL;
    /* Extraction. */
    assert_non_null(infos_extract = stegx_init(&choices_extract));
    assert_false(stegx_check_compatibility(infos_extract));
    assert_false(stegx_detect_algo(infos_extract));
    assert_false(stegx_extract(infos_extract, choices_extract.res_path));
    stegx_clear(infos_extract);

    /* Comparaison du fichier caché original avec le fichier extrait. */
    size = 0;
    assert_non_null(fsrc = fopen(TEST_DIR"others/short.txt", "rb"));
    assert_non_null(fdst = fopen("short.txt", "rb"));
    for (uint8_t bsrc, bdst; fread(&bdst, sizeof(bdst), 1, fdst); size++)
        fread(&bsrc, sizeof(bsrc), 1, fsrc), assert_int_equal(bsrc, bdst);
    assert_int_equal(size, 27);

    /* Nettoyage. */
    assert_false(remove("test_lsb_mp3")), assert_false(remove("short.txt"));
    assert_false(fclose(fsrc)); assert_false(fclose(fdst));

    /* Fichier en ID3v2.3 sans mot de passe. */

    /* Initialisation insertion. */
    choices_insert.host_path = TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_1.mp3";
    choices_insert.res_path = "test_lsb_mp3";
    choices_insert.passwd = NULL;
    choices_insert.mode = STEGX_MODE_INSERT;
    choices_insert.insert_info = &choices_insert_info;
    choices_insert.insert_info->hidden_path = TEST_DIR"others/test16.txt";
    choices_insert.insert_info->algo = STEGX_ALGO_LSB;
    /* Insertion. */
    assert_non_null(infos_insert = stegx_init(&choices_insert));
    assert_false(stegx_check_compatibility(infos_insert));
    assert_false(stegx_suggest_algo(infos_insert));
    assert_false(stegx_choose_algo(infos_insert, choices_insert.insert_info->algo));
    assert_false(stegx_insert(infos_insert));
    stegx_clear(infos_insert);

    /* Vérifie que le fichier stégo n'as pas été altéré. */
    assert_non_null(fstego = fopen("test_lsb_mp3", "rb"));
    assert_non_null(forig = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_1.mp3", "rb"));
    /* On prend quelques échantillons représentatif pour vérifier que le fichier n'as pas été
     * altéré. */
    dst32 = src32 = 0;
    /* Échantillon d'un header MPEG. */
    assert_false(fseek(fstego, 0x395, SEEK_SET)), assert_false(fseek(forig, 0x395, SEEK_SET));
    assert_true(fread(&dst32, sizeof(uint16_t), 1, fstego)), assert_true(fread(&src32, sizeof(uint16_t), 1, forig));
    assert_int_equal(dst32, src32);
    /* Échantillon d'un tag ID3v2.3. */
    assert_false(fseek(fstego, 0x93, SEEK_SET)), assert_false(fseek(forig, 0x93, SEEK_SET));
    assert_true(fread(&dst32, sizeof(dst32), 1, fstego)), assert_true(fread(&src32, sizeof(dst32), 1, forig));
    assert_int_equal(dst32, src32);
    /* Échantillon d'une frame MPEG. */
    assert_false(fseek(fstego, 0x1995, SEEK_SET)), assert_false(fseek(forig, 0x1995, SEEK_SET));
    assert_true(fread(&dst32, sizeof(dst32), 1, fstego)), assert_true(fread(&src32, sizeof(dst32), 1, forig));
    assert_int_equal(dst32, src32);
    /* Échantillon d'un tag ID3v1. */
    assert_false(fseek(fstego, 0x4947C0, SEEK_SET)), assert_false(fseek(forig, 0X4947C0, SEEK_SET));
    assert_true(fread(&dst32, sizeof(dst32), 1, fstego)), assert_true(fread(&src32, sizeof(dst32), 1, forig));
    assert_int_equal(dst32, src32);
    /* Fermeture. */
    assert_false(fclose(fstego)), assert_false(fclose(forig));

    /* Initialisation extraction. */
    choices_extract.host_path = "test_lsb_mp3";
    choices_extract.res_path = "./";
    choices_extract.passwd = NULL;
    choices_extract.mode = STEGX_MODE_EXTRACT;
    choices_extract.insert_info = NULL;
    /* Extraction. */
    assert_non_null(infos_extract = stegx_init(&choices_extract));
    assert_false(stegx_check_compatibility(infos_extract));
    assert_false(stegx_detect_algo(infos_extract));
    assert_false(stegx_extract(infos_extract, choices_extract.res_path));
    stegx_clear(infos_extract);

    /* Comparaison du fichier caché original avec le fichier extrait. */
    size = 0;
    assert_non_null(fsrc = fopen(TEST_DIR"others/test16.txt", "rb"));
    assert_non_null(fdst = fopen("test16.txt", "rb"));
    for (uint8_t bsrc, bdst; fread(&bdst, sizeof(bdst), 1, fdst); size++)
        fread(&bsrc, sizeof(bsrc), 1, fsrc), assert_int_equal(bsrc, bdst);
    assert_int_equal(size, 14);

    /* Nettoyage. */
    assert_false(remove("test_lsb_mp3")), assert_false(remove("test16.txt"));
    assert_false(fclose(fsrc)); assert_false(fclose(fdst));
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest lsb_tests[] = {
    cmocka_unit_test(test_lsb_little_bmp_with_passwd),
    cmocka_unit_test(test_lsb_little_bmp_without_passwd),
    cmocka_unit_test(test_lsb_big_bmp_with_passwd),
    cmocka_unit_test(test_lsb_big_bmp_without_passwd),
    cmocka_unit_test(test_lsb_mp3)
};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(lsb_tests, NULL, NULL);
}
