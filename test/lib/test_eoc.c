#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "stegx.h"
#include "common.h"

/*
 *  Test de l'algo End of Chunk pour les fichiers FLV ==================
 * */
 
/* Test avec l'algo de protection des données */
void test_eoc_protection(void **state){
	(void)state;
    // Initialisation de l'insertion
    stegx_choices_s *choices = malloc(sizeof(stegx_choices_s));
    assert_non_null(choices);
	choices->host_path = "../../../env/test/flv/test13.flv",
		assert_non_null(choices->host_path);
    choices->res_path = "./res_test_eoc.flv",
		assert_non_null(choices->res_path);    
    choices->mode = STEGX_MODE_INSERT;
    choices->passwd = "stegx";
    choices->insert_info = malloc(sizeof(stegx_info_insert_s)),
		assert_non_null(choices->insert_info);
    choices->insert_info->hidden_path = "../../../env/test/others/short.txt",
		assert_non_null(choices->insert_info->hidden_path);
    choices->insert_info->algo = STEGX_ALGO_EOC;    
    info_s *infos = stegx_init(choices);
    assert_non_null(infos);
    
    //Insertion
    assert_int_equal(stegx_check_compatibility(infos), 0);
    assert_int_equal(stegx_suggest_algo(infos), 0);
    assert_int_equal(stegx_choose_algo(infos, choices->insert_info->algo), 0);
    assert_int_equal(stegx_insert(infos), 0);
    
    //Libération de la mémoire
    stegx_clear(infos);
	free(choices->insert_info);
	free(choices);
	
	// Initialisation de l'extraction
    choices = malloc(sizeof(stegx_choices_s));
    assert_non_null(choices);
	choices->host_path = "./res_test_eoc.flv",
		assert_non_null(choices->host_path);
    choices->res_path = "./",
		assert_non_null(choices->res_path);    
    choices->mode = STEGX_MODE_EXTRACT;
    choices->passwd = "stegx";
    choices->insert_info = NULL;    
    infos = stegx_init(choices);
    assert_non_null(infos);
    
    //Extraction
    assert_int_equal(stegx_check_compatibility(infos), 0);
    assert_int_equal(stegx_detect_algo(infos), 0);
	assert_int_equal(stegx_extract(infos, choices->res_path), 0);
	
	uint32_t length_file = infos->hidden_length;
	
	//Libération de la mémoire
    stegx_clear(infos);
	free(choices->insert_info);
	free(choices);
	
	//Teste le résultat de l'extraction
	char *message = calloc(length_file+1, sizeof(char));
    FILE *f = fopen("./short.txt", "r");
    fread(message, sizeof(char), length_file-2, f);
    assert_int_equal(strcmp(message, "voici un test tres court."), 0);
    fclose(f);
    remove("./short.txt");
}

void test_eoc_no_protection(void **state){
	(void)state;
}

/*
 * MAIN ================================================================
 * */
 
int main(void)
{
	/* Structure CMocka contenant la liste des tests. */
	const struct CMUnitTest eoc_tests[] = {
		cmocka_unit_test(test_eoc_protection),
		cmocka_unit_test(test_eoc_no_protection)
		};
	
	/* Exécute les tests. */
    return cmocka_run_group_tests(eoc_tests, NULL, NULL);
		
}
