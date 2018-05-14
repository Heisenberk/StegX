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

void free_infos(info_s * infos)
{
    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);
}

void test_insert_eof_bmp_with_passwd(void **state)
{
    (void)state;
    info_s *infos_insert = malloc(sizeof(info_s));
    infos_insert->mode = STEGX_MODE_INSERT;
    infos_insert->algo = STEGX_ALGO_EOF;
    infos_insert->method = STEGX_WITH_PASSWD;
    infos_insert->host.host = fopen("../../../env/test/test9bis.bmp", "r");
    infos_insert->host.type = BMP_COMPRESSED;
    infos_insert->res = fopen("res1_test_eof.bmp", "w");
    infos_insert->hidden_name = malloc((strlen("short.txt") + 1) * sizeof(char));
    char *hidden_name_write = malloc((strlen("short.txt") + 1) * sizeof(char));
    strcpy(infos_insert->hidden_name, "short.txt");
    strcpy(hidden_name_write, "short.txt");
    infos_insert->hidden = fopen("../../../env/test/short.txt", "r");
    infos_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos_insert->passwd, "stegx");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    // insertion de short.txt dans test9bis.bmp 
    stegx_suggest_algo(infos_insert);
    stegx_choose_algo(infos_insert, STEGX_ALGO_EOF);
    uint32_t hidden_length_insert = infos_insert->hidden_length;
    stegx_insert(infos_insert);

    // libéreation de infos_insert car reutilisation des memes fichiers par la suite
    free_infos(infos_insert);

    // extraction de short.txt dans test9bis.bmp
    info_s *infos_extract = malloc(sizeof(info_s));
    infos_extract->mode = STEGX_MODE_EXTRACT;
    infos_extract->method = STEGX_WITH_PASSWD;
    infos_extract->host.host = fopen("res1_test_eof.bmp", "r");
    infos_extract->host.type = BMP_COMPRESSED;
    infos_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos_extract->passwd, "stegx");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    stegx_detect_algo(infos_extract);
    stegx_extract(infos_extract, "./");
    uint32_t hidden_length_extract = infos_extract->hidden_length;
    char *hidden_name = malloc((strlen(infos_extract->hidden_name) + 1) * sizeof(char));
    strcpy(hidden_name, infos_extract->hidden_name);

    // Test si le fichier extrait fait la bonne taille
    int test_length = (hidden_length_insert == hidden_length_extract);
    assert_int_equal(test_length, 1);

    // Test si le même nom a bien été interprété
    int test_name = (strcmp(hidden_name, infos_extract->hidden_name) == 0);
    assert_int_equal(test_name, 1);

    free_infos(infos_extract);
    free(hidden_name);

	
    int test_content = 1;
    uint8_t c;
    uint32_t i;
    char *message = malloc((infos_extract->hidden_length + 1) * sizeof(char));
    FILE *f = fopen("./short.txt", "r");
    if (f == NULL)
        test_content = 0;
    for (i = 0; i < (infos_extract->hidden_length) - 1; i++) {
        fread(&c, sizeof(uint8_t), 1, f);
        message[i] = c;
    }
    message[infos_extract->hidden_length - 2] = '\0';
    // Test si le contenu du message a bien ete extrait
    test_name = (strcmp(message, "voici un test tres court.") == 0);
    if (test_content == 0)
        test_name = 0;
    assert_int_equal(test_name, 1);
    free(message);
    remove("./short.txt");
}

void test_insert_eof_bmp_without_passwd(void **state)
{
    (void)state;
    info_s *infos_insert = malloc(sizeof(info_s));
    infos_insert->mode = STEGX_MODE_INSERT;
    infos_insert->algo = STEGX_ALGO_EOF;
    infos_insert->method = STEGX_WITHOUT_PASSWD;
    infos_insert->host.host = fopen("../../../env/test/test9bis.bmp", "r");
    infos_insert->host.type = BMP_COMPRESSED;
    infos_insert->res = fopen("res2_test_eof.bmp", "w");
    infos_insert->hidden_name = malloc((strlen("short.txt") + 1) * sizeof(char));
    char *hidden_name_write = malloc((strlen("short.txt") + 1) * sizeof(char));
    strcpy(infos_insert->hidden_name, "short.txt");
    strcpy(hidden_name_write, "short.txt");
    infos_insert->hidden = fopen("../../../env/test/short.txt", "r");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    // insertion de short.txt dans test9bis.bmp 
    stegx_suggest_algo(infos_insert);
    stegx_choose_algo(infos_insert, STEGX_ALGO_EOF);
    uint32_t hidden_length_insert = infos_insert->hidden_length;
    stegx_insert(infos_insert);

    free_infos(infos_insert);

    info_s *infos_extract = malloc(sizeof(info_s));
    infos_extract->mode = STEGX_MODE_EXTRACT;
    infos_extract->method = STEGX_WITHOUT_PASSWD;
    infos_extract->host.host = fopen("res2_test_eof.bmp", "r");
    infos_extract->host.type = BMP_COMPRESSED;
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    // extraction de short.txt dans test9bis.bmp
    stegx_detect_algo(infos_extract);
    stegx_extract(infos_extract, "./");
    uint32_t hidden_length_extract = infos_extract->hidden_length;
    char *hidden_name = malloc((strlen(infos_extract->hidden_name) + 1) * sizeof(char));
    strcpy(hidden_name, infos_extract->hidden_name);

    // Test si le fichier extrait fait la bonne taille
    int test_length = (hidden_length_insert == hidden_length_extract);
    assert_int_equal(test_length, 1);

    // Test si le même nom a bien été interprété
    int test_name = (strcmp(hidden_name, infos_extract->hidden_name) == 0);
    assert_int_equal(test_name, 1);

    free_infos(infos_extract);
    free(hidden_name);

	uint8_t i;
    int test_content = 1;
    uint8_t c;
    char *message = malloc((infos_extract->hidden_length + 1) * sizeof(char));
    FILE *f = fopen("./short.txt", "r");
    if (f == NULL)
        test_content = 0;
    for (i = 0; i < (infos_extract->hidden_length) - 1; i++) {
        fread(&c, sizeof(uint8_t), 1, f);
        message[i] = c;
    }
    message[infos_extract->hidden_length - 2] = '\0';
    // Test si le contenu du message a bien ete extrait
    test_name = (strcmp(message, "voici un test tres court.") == 0);
    if (test_content == 0)
        test_name = 0;
    assert_int_equal(test_name, 1);
    free(message);
    remove("./short.txt");
}

void test_insert_eof_png_with_passwd(void **state)
{
    (void)state;
    info_s *infos_insert = malloc(sizeof(info_s));
    infos_insert->mode = STEGX_MODE_INSERT;
    infos_insert->algo = STEGX_ALGO_EOF;
    infos_insert->method = STEGX_WITH_PASSWD;
    infos_insert->host.host = fopen("../../../env/test/test8.png", "r");
    infos_insert->host.type = PNG;
    infos_insert->res = fopen("res3_test_eof.png", "w");
    infos_insert->hidden_name = malloc((strlen("short.txt") + 1) * sizeof(char));
    char *hidden_name_write = malloc((strlen("short.txt") + 1) * sizeof(char));
    strcpy(infos_insert->hidden_name, "short.txt");
    strcpy(hidden_name_write, "short.txt");
    infos_insert->hidden = fopen("../../../env/test/short.txt", "r");
    infos_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos_insert->passwd, "stegx");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    // insertion de short.txt dans test8.png 
    stegx_suggest_algo(infos_insert);
    stegx_choose_algo(infos_insert, STEGX_ALGO_EOF);
    uint32_t hidden_length_insert = infos_insert->hidden_length;
    stegx_insert(infos_insert);

    free_infos(infos_insert);

    // extraction de short.txt dans test8.png
    info_s *infos_extract = malloc(sizeof(info_s));
    infos_extract->mode = STEGX_MODE_EXTRACT;
    infos_extract->method = STEGX_WITH_PASSWD;
    infos_extract->host.host = fopen("res3_test_eof.png", "r");
    infos_extract->host.type = PNG;
    infos_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos_extract->passwd, "stegx");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    stegx_detect_algo(infos_extract);
    stegx_extract(infos_extract, "./");
    uint32_t hidden_length_extract = infos_extract->hidden_length;
    char *hidden_name = malloc((strlen(infos_extract->hidden_name) + 1) * sizeof(char));
    strcpy(hidden_name, infos_extract->hidden_name);

    // Test si le fichier extrait fait la bonne taille
    int test_length = (hidden_length_insert == hidden_length_extract);
    assert_int_equal(test_length, 1);

    // Test si le même nom a bien été interprété
    int test_name = (strcmp(hidden_name, infos_extract->hidden_name) == 0);
    assert_int_equal(test_name, 1);

    free_infos(infos_extract);
    free(hidden_name);

	uint8_t i;
    int test_content = 1;
    uint8_t c;
    char *message = malloc((infos_extract->hidden_length + 1) * sizeof(char));
    FILE *f = fopen("./short.txt", "r");
    if (f == NULL)
        test_content = 0;
    for (i = 0; i < (infos_extract->hidden_length) - 1; i++) {
        fread(&c, sizeof(uint8_t), 1, f);
        message[i] = c;
    }
    message[infos_extract->hidden_length - 2] = '\0';

    // Test si le contenu du message a bien ete extrait
    printf("%s,%s", message, "voici un test tres court.");
    test_name = (strcmp(message, "voici un test tres court.") == 0);
    if (test_content == 0)
        test_name = 0;
    assert_int_equal(test_name, 1);
    free(message);
    remove("./short.txt");
}

void test_insert_eof_png_without_passwd(void **state)
{
    (void)state;
    info_s *infos_insert = malloc(sizeof(info_s));
    infos_insert->mode = STEGX_MODE_INSERT;
    infos_insert->algo = STEGX_ALGO_EOF;
    infos_insert->method = STEGX_WITHOUT_PASSWD;
    infos_insert->host.host = fopen("../../../env/test/test9.png", "r");
    infos_insert->host.type = PNG;
    infos_insert->res = fopen("res4_test_eof.png", "w");
    infos_insert->hidden_name = malloc((strlen("short.txt") + 1) * sizeof(char));
    char *hidden_name_write = malloc((strlen("short.txt") + 1) * sizeof(char));
    strcpy(infos_insert->hidden_name, "short.txt");
    strcpy(hidden_name_write, "short.txt");
    infos_insert->hidden = fopen("../../../env/test/short.txt", "r");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    // insertion de short.txt dans test8.png 
    stegx_suggest_algo(infos_insert);
    stegx_choose_algo(infos_insert, STEGX_ALGO_EOF);
    uint32_t hidden_length_insert = infos_insert->hidden_length;
    stegx_insert(infos_insert);

    free_infos(infos_insert);

    info_s *infos_extract = malloc(sizeof(info_s));
    infos_extract->mode = STEGX_MODE_EXTRACT;
    infos_extract->method = STEGX_WITHOUT_PASSWD;
    infos_extract->host.host = fopen("res4_test_eof.png", "r");
    infos_extract->host.type = PNG;
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    // extraction de short.txt dans test8.png
    stegx_detect_algo(infos_extract);
    stegx_extract(infos_extract, "./");
    uint32_t hidden_length_extract = infos_extract->hidden_length;
    char *hidden_name = malloc((strlen(infos_extract->hidden_name) + 1) * sizeof(char));
    strcpy(hidden_name, infos_extract->hidden_name);

    // Test si le fichier extrait fait la bonne taille
    int test_length = (hidden_length_insert == hidden_length_extract);
    assert_int_equal(test_length, 1);

    // Test si le même nom a bien été interprété
    int test_name = (strcmp(hidden_name, infos_extract->hidden_name) == 0);
    assert_int_equal(test_name, 1);

    free_infos(infos_extract);
    free(hidden_name);

	uint8_t i;
    int test_content = 1;
    uint8_t c;
    char *message = malloc((infos_extract->hidden_length + 1) * sizeof(char));
    FILE *f = fopen("./short.txt", "r");
    if (f == NULL)
        printf("coucou");       //test_content=0;
    for (i = 0; i < (infos_extract->hidden_length) - 1; i++) {
        fread(&c, sizeof(uint8_t), 1, f);
        message[i] = c;
    }
    message[infos_extract->hidden_length - 2] = '\0';
    // Test si le contenu du message a bien ete extrait
    test_name = (strcmp(message, "voici un test tres court.") == 0);
    if (test_content == 0)
        test_name = 0;
    assert_int_equal(test_name, 1);
    free(message);
    remove("./short.txt");
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest insert_eof_tests[] = {

    /*cmocka_unit_test(test_insert_eof_bmp_with_passwd),
       cmocka_unit_test(test_insert_eof_bmp_without_passwd),
       cmocka_unit_test(test_insert_eof_png_with_passwd),
       cmocka_unit_test(test_insert_eof_png_without_passwd), */
};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(insert_eof_tests, NULL, NULL);
}
