/* Inclusions minimales. */
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

/* Inclusions supplémentaires. */
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "stegx.h"
#include "common.h"


/*setup des tests unitaire pour l'écriture de la signature */
static int test_write_signature_setup(void **state){
	info_s *infos = malloc(sizeof(info_s));
    assert_non_null(infos);
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->host.host = fopen("../../../env/test/test1.bmp", "r"),assert_non_null(infos->host.host);
    infos->host.type = BMP_COMPRESSED;
    infos->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char)),assert_non_null(infos->hidden_name);
    strcpy(infos->hidden_name, "test2.bmp");
    infos->hidden = fopen("../../../env/test/test2.bmp", "r"),assert_non_null(infos->hidden_name);
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e)),assert_non_null(stegx_propos_algos);
    *state = infos;
    return 0;
}

/* teardown des tests unitaire pour l'écriture de la signature */
static int test_write_signature_teardown(void **state){
	info_s *infos = *state;
    fclose(infos->hidden);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);
    return 0;
}

/* test de la signature avec mot de passe */
void test_write_signature_with_passwd(void **state){
	info_s *infos = *state;
	infos->method = STEGX_WITH_PASSWD;
	infos->res = fopen("res1_test_insert.bmp", "w"),assert_non_null(infos->res);
	infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos->passwd, "stegx");
	stegx_suggest_algo(infos);
    stegx_choose_algo(infos, STEGX_ALGO_EOF);
    write_signature(infos);
    fclose(infos->res);

    // variables utilisées pour la lecture
    uint8_t algo_read, method, length_name;
    uint32_t length_file;
    char hidden_name[LENGTH_HIDDEN_NAME_MAX + 1] = {0};
	FILE *f = fopen("res1_test_insert.bmp", "r");
    // lecture de l'algorithme
    fread(&algo_read, sizeof(uint8_t), 1, f);
	// lecture de la méthode de protection de donnée
    fread(&method, sizeof(uint8_t), 1, f);
	// lecture de la taille du fichier caché
    fread(&length_file, sizeof(uint32_t), 1, f);
	// lecture de la taille du nom du fichier caché
    fread(&length_name, sizeof(uint8_t), 1, f);
	// lecture du nom du fichier caché XOR le mot de passe choisi par l'utilisateur
    fread(hidden_name, sizeof(char), length_name, f);
    for (int i = 0, j = 0 ; i < length_name ; i++) {
        hidden_name[i] = hidden_name[i] ^ infos->passwd[j];
        j = infos->passwd[j + 1] ? j + 1 : 0; /* Boucle sur le mot de passe. */
    }
    //ALGO
	assert_int_equal(algo_read, STEGX_ALGO_EOF);
    //METHOD
    assert_int_equal(method, STEGX_WITH_PASSWD);
    //taille du fichier caché
    assert_int_equal(length_file, 14057098);
    //nom du fichier caché
    assert_int_equal(strcmp(hidden_name, infos->hidden_name), 0);

}

/* test de la signature sans mot de passe */
void test_write_signature_without_passwd(void **state){
	info_s *infos = *state;
	infos->method = STEGX_WITHOUT_PASSWD;
	infos->res = fopen("res2_test_insert.bmp", "w"),assert_non_null(infos->res);
	stegx_suggest_algo(infos);
    stegx_choose_algo(infos, STEGX_ALGO_EOF);
    write_signature(infos);
	fclose(infos->res);
	
	// variables utilisées pour la lecture
	uint8_t algo_read, method, length_name;
    uint32_t length_file;
	char hidden_name[LENGTH_HIDDEN_NAME_MAX + 1] = {0};    
    FILE *f = fopen("res2_test_insert.bmp", "r");
    // lecture de l'algorithme
    fread(&algo_read, sizeof(uint8_t), 1, f);
    
    // lecture de la méthode de protection de donnée
    fread(&method, sizeof(uint8_t), 1, f);

    // lecture de la taille du fichier caché
    fread(&length_file, sizeof(uint32_t), 1, f);

    // lecture de la taille du nom du fichier caché
    fread(&length_name, sizeof(uint8_t), 1, f);

    // lecture du nom du fichier caché XOR le mot de passe choisi par l'utilisateur
	fread(hidden_name, sizeof(char), length_name, f);
    for (int i = 0, j = 0 ; i < length_name ; i++) {
        hidden_name[i] = hidden_name[i] ^ infos->passwd[j];
        j = infos->passwd[j + 1] ? j + 1 : 0; /* Boucle sur le mot de passe. */
    }

    // lecture du mot de passe par défaut choisi aleatoirement par l'application
    // aller jusqu'au debut de la lecture du mot de passe
    char passwd_read[LENGTH_DEFAULT_PASSWD + 1] = {0};
    fread(passwd_read, sizeof(char), LENGTH_DEFAULT_PASSWD, f);

    //ALGO
    assert_int_equal(algo_read, STEGX_ALGO_EOF);
    //METHOD
    assert_int_equal(method, STEGX_WITHOUT_PASSWD);
    //taille du fichier caché
    assert_int_equal(length_file, 14057098);
    //nom du fichier caché
    assert_int_equal(strcmp(hidden_name, infos->hidden_name), 0);
    //mot de passe par default 
    assert_int_equal(strcmp(passwd_read, infos->passwd), 0);
}

int main(void)
{

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest check_insert_tests[] = {
    cmocka_unit_test(test_write_signature_with_passwd),
    cmocka_unit_test(test_write_signature_without_passwd),
};

    /* Exécute les tests. */
    return cmocka_run_group_tests(check_insert_tests, test_write_signature_setup, test_write_signature_teardown);
}
