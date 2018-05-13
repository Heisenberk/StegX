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

uint32_t hidden_length = 0;

/**
 * Test detectection de l'algo avec mot de passe.
 * =====================================================================
 * */

/* Initialisation du test, insertion des données dans un fichier. */
void insert_with_passwd(void **state)
{
    /* Initialisation de l'insertion */
    (void)state;
    info_s *infos_insert = malloc(sizeof(info_s));
    infos_insert->mode = STEGX_MODE_INSERT;
    infos_insert->method = STEGX_WITH_PASSWD;
    infos_insert->host.host = fopen("../../../env/test/test1.bmp", "r"),
					assert_non_null(infos_insert->host.host);
    infos_insert->host.type = BMP_COMPRESSED;
    infos_insert->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char)),
				assert_non_null(infos_insert->hidden_name);
    strcpy(infos_insert->hidden_name, "test2.bmp");
    infos_insert->hidden = fopen("../../../env/test/test2.bmp", "r"),
				assert_non_null(infos_insert->hidden);	
    infos_insert->res = fopen("res3_test_insert.bmp", "w"),
				assert_non_null(infos_insert->res);
    infos_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char)),
				assert_non_null(infos_insert->passwd);
    strcpy(infos_insert->passwd, "stegx");
	stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e)),
				assert_non_null(stegx_propos_algos);

	/* Choix de l'algo et insertion */
    assert_int_equal(stegx_suggest_algo(infos_insert), 0);
    assert_int_equal(stegx_choose_algo(infos_insert, STEGX_ALGO_EOF), 0);
    assert_int_equal(stegx_insert(infos_insert), 0);

	/* Sauvegarder de la taille du fichier à inserer */
    hidden_length = infos_insert->hidden_length;
	
	/* Libération de la mémoire pour l'insertion */
    fclose(infos_insert->host.host);
    fclose(infos_insert->res);
    free(infos_insert->hidden_name);
    free(infos_insert->passwd);
    free(infos_insert);
    free(stegx_propos_algos);
}

/* Teste la fonction stegx_detect_algo. Fais l'extration de la signature */
void detect_with_passwd(void **state)
{
    (void) state; /* Unused. */

	/* Initialisation de l'extraction */
    info_s *infos_extract = malloc(sizeof(info_s));
    infos_extract->mode = STEGX_MODE_EXTRACT;
    infos_extract->host.host = fopen("res3_test_insert.bmp", "r"),
				assert_non_null(infos_extract->host.host);
    infos_extract->res = fopen("res3_test_extract.bmp", "w"),
				assert_non_null(infos_extract->res);
    infos_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char)),
				assert_non_null(infos_extract->passwd);
    strcpy(infos_extract->passwd, "stegx");
	
	/* Vérification de la compatibilité et extraction des informations
	 *  dans la signature du fichier.*/
    assert_int_equal(stegx_check_compatibility(infos_extract), 0);
    assert_int_equal(stegx_detect_algo(infos_extract), 0);

    /* on compare l'algorithme, la méthode, la taille du fichier caché et
     *  le nom du fichier caché. */
    assert_int_equal(infos_extract->algo, STEGX_ALGO_EOF);
    assert_int_equal(infos_extract->method, STEGX_WITH_PASSWD);
    assert_int_equal(infos_extract->hidden_length, hidden_length);
    assert_int_equal(strcmp(infos_extract->hidden_name, "test2.bmp"), 0);
	
	/* Libération de la mémoire pour l'extraction. */
    fclose(infos_extract->host.host);
    fclose(infos_extract->res);
    free(infos_extract->hidden_name);
    free(infos_extract->passwd);
    free(infos_extract);
}

/**
 * Test detectection de l'algo sans mot de passe.
 * =====================================================================
 * */

/* Initialisation du test, insertion des données dans un fichier. */
void insert_without_passwd(void **state)
{
    /* Initialisation de l'insertion */
    (void)state;
    info_s *infos_insert = malloc(sizeof(info_s));
    infos_insert->mode = STEGX_MODE_INSERT;
    infos_insert->method = STEGX_WITHOUT_PASSWD;
    infos_insert->host.host = fopen("../../../env/test/test1.bmp", "r"),
					assert_non_null(infos_insert->host.host);
    infos_insert->host.type = BMP_COMPRESSED;
    infos_insert->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char)),
				assert_non_null(infos_insert->hidden_name);
    strcpy(infos_insert->hidden_name, "test2.bmp");
    infos_insert->hidden = fopen("../../../env/test/test2.bmp", "r"),
				assert_non_null(infos_insert->hidden);	
    infos_insert->res = fopen("res4_test_insert.bmp", "w"),
				assert_non_null(infos_insert->res);
	stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e)),
				assert_non_null(stegx_propos_algos);

	/* Choix de l'algo et insertion */
    assert_int_equal(stegx_suggest_algo(infos_insert), 0);
    assert_int_equal(stegx_choose_algo(infos_insert, STEGX_ALGO_EOF), 0);
    assert_int_equal(stegx_insert(infos_insert), 0);

	/* Sauvegarder de la taille du fichier à inserer */
    hidden_length = infos_insert->hidden_length;
	
	/* Libération de la mémoire pour l'insertion */
    fclose(infos_insert->host.host);
    fclose(infos_insert->res);
    free(infos_insert->hidden_name);
	free(infos_insert);
    free(stegx_propos_algos);
    
}

/* Teste la fonction stegx_detect_algo. Fais l'extration de la signature */
void detect_without_passwd(void **state)
{
    (void) state; /* Unused. */
	/* Initialisation de l'extraction */
    info_s *infos_extract = malloc(sizeof(info_s));
    infos_extract->mode = STEGX_MODE_EXTRACT;
    infos_extract->host.host = fopen("res4_test_insert.bmp", "r"),
				assert_non_null(infos_extract->host.host);
    infos_extract->res = fopen("res4_test_extract.bmp", "w"),
				assert_non_null(infos_extract->res);

	/* Vérification de la compatibilité et extraction des informations
	 *  dans la signature du fichier.*/
    assert_int_equal(stegx_check_compatibility(infos_extract), 0);
    assert_int_equal(stegx_detect_algo(infos_extract), 0);

    /* on compare l'algorithme, la méthode, la taille du fichier caché et
     *  le nom du fichier caché. */
    assert_int_equal(infos_extract->algo, STEGX_ALGO_EOF);
    assert_int_equal(infos_extract->method, STEGX_WITHOUT_PASSWD);
    assert_int_equal(infos_extract->hidden_length, hidden_length);
    assert_int_equal(strcmp(infos_extract->hidden_name, "test2.bmp"), 0);
	
	/* Libération de la mémoire pour l'extraction. */
    fclose(infos_extract->host.host);
    fclose(infos_extract->res);
    free(infos_extract->hidden_name);
    free(infos_extract);
}

/**
 * MAIN
 * =====================================================================
 * */
 
int main(void)
{
	/* Structures CMocka contenant la liste des tests. */
	const struct CMUnitTest test_detect_algo_with_passwd[] = {
		cmocka_unit_test(insert_with_passwd),
		cmocka_unit_test(detect_with_passwd),
	};

	const struct CMUnitTest test_detect_algo_without_passwd[] =
	{
		cmocka_unit_test(insert_without_passwd),
		cmocka_unit_test(detect_without_passwd)
	};

    /* Exécute les tests. */
    return cmocka_run_group_tests(test_detect_algo_with_passwd, NULL, NULL)
			+ cmocka_run_group_tests(test_detect_algo_without_passwd, NULL, NULL);    
}
