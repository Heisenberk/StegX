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

extern int fill_host_info(info_s * infos);
extern int write_signature(info_s * infos);

void test_write_signature_with_passwd(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->host.host = fopen("../../../env/test/test1.bmp", "r");
    infos->host.type = BMP_COMPRESSED;
    infos->res = fopen("res1_test_insert.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    char *hidden_name_write = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    strcpy(hidden_name_write, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    char *passwd_save = malloc((strlen("stegx") + 1) * sizeof(char));
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");
    strcpy(passwd_save, "stegx");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    stegx_suggest_algo(infos);
    stegx_choose_algo(infos, STEGX_ALGO_EOF);
    write_signature(infos);

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);

    uint8_t algo_read, length_name;
    uint32_t length_file;
    FILE *f = fopen("res1_test_insert.bmp", "r");
    // lecture de l'algorithme
    fread(&algo_read, sizeof(uint8_t), 1, f);

    // lecture de la taille du fichier caché
    fread(&length_file, sizeof(uint32_t), 1, f);
    length_file = be32toh(length_file);

    // lecture de la taille du nom du fichier caché
    fread(&length_name, sizeof(uint8_t), 1, f);

    // lecture du nom du fichier caché XOR le mot de passe choisi par l'utilisateur
    char *hidden_name = malloc((length_name + 1) * sizeof(char));
    int i = 0, j = 0;
    uint8_t c;
    while (i < length_name) {
        fread(&c, sizeof(uint8_t), 1, f);
        hidden_name[i] = c ^ passwd_save[j];
        i++;
        j++;
        if (passwd_save[j] == '\0')
            j = 0;
    }
    hidden_name[length_name] = '\0';

    int test = ((algo_read == BYTE_EOF_WITH_PASSWD) && (length_file == 14057098) &&
                (strcmp(hidden_name, hidden_name_write) == 0));
    if(f!=NULL) fclose(f);
    if (hidden_name != NULL)
    free(hidden_name);
    free(hidden_name_write);
    free(passwd_save);

    assert_int_equal(test, 1);
}

void test_write_signature_without_passwd(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITHOUT_PASSWD;
    infos->host.host = fopen("../../../env/test/test1.bmp", "r");
    infos->host.type = BMP_COMPRESSED;
    infos->res = fopen("res2_test_insert.bmp", "w");
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    char *hidden_name_write = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos->hidden_name, "test2.bmp");
    strcpy(hidden_name_write, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    stegx_suggest_algo(infos);
    stegx_choose_algo(infos, STEGX_ALGO_EOF);
    char *passwd_save = malloc((strlen(infos->passwd) + 1) * sizeof(char));
    strcpy(passwd_save, infos->passwd);
    write_signature(infos);

    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->res != NULL)
        fclose(infos->res);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);

    uint8_t algo_read, length_name;
    uint32_t length_file;
    FILE *f = fopen("res2_test_insert.bmp", "r");
    // lecture de l'algorithme
    fread(&algo_read, sizeof(uint8_t), 1, f);

    // lecture de la taille du fichier caché
    fread(&length_file, sizeof(uint32_t), 1, f);
    length_file = be32toh(length_file);

    // lecture de la taille du nom du fichier caché
    fread(&length_name, sizeof(uint8_t), 1, f);

    // lecture du nom du fichier caché XOR le mot de passe choisi par l'utilisateur
    char *hidden_name = malloc((length_name + 1) * sizeof(char));
    int i = 0, j = 0;
    uint8_t c;
    while (i < length_name) {
        fread(&c, sizeof(uint8_t), 1, f);
        hidden_name[i] = c ^ passwd_save[j];
        i++;
        j++;
        if (passwd_save[j] == '\0')
            j = 0;
    }
    hidden_name[length_name] = '\0';

    // lecture du mot de passe par défaut choisi aleatoirement par l'application
    // aller jusqu'au debut de la lecture du mot de passe
    char *passwd_read = malloc((LENGTH_DEFAULT_PASSWD + 1) * sizeof(char));
    for (i = 0; i < LENGTH_DEFAULT_PASSWD + 1; i++) {
        fread(&c, sizeof(uint8_t), 1, f);
        passwd_read[i] = c;
    }
    passwd_read[LENGTH_DEFAULT_PASSWD] = '\0';

    int test = ((algo_read == BYTE_EOF_WITHOUT_PASSWD) && (length_file == 14057098) &&
                (strcmp(hidden_name, hidden_name_write) == 0)
                && (strcmp(passwd_read, passwd_save) == 0));
    if(f!=NULL) fclose(f);
    free(hidden_name);
    free(hidden_name_write);
    free(passwd_save);
    free(passwd_read);

    assert_int_equal(test, 1);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest check_compatibility_tests[] = {

    cmocka_unit_test(test_write_signature_with_passwd),
    cmocka_unit_test(test_write_signature_without_passwd),

};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(check_compatibility_tests, NULL, NULL);
}
