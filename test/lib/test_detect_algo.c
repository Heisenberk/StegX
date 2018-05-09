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

void test_detect_algo_with_passwd(void **state)
{
    (void)state;
    info_s *infos_insert = malloc(sizeof(info_s));
    infos_insert->mode = STEGX_MODE_INSERT;
    infos_insert->algo = STEGX_ALGO_EOF;
    infos_insert->method = STEGX_WITH_PASSWD;
    infos_insert->host.host = fopen("../../../env/test/test1.bmp", "r");
    infos_insert->host.type = BMP_COMPRESSED;
    infos_insert->res = fopen("res3_test_insert.bmp", "w");
    infos_insert->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    char *hidden_name_write1 = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos_insert->hidden_name, "test2.bmp");
    strcpy(hidden_name_write1, "test2.bmp");
    infos_insert->hidden = fopen("../../../env/test/test2.bmp", "r");
    char *passwd_save1 = malloc((strlen("stegx") + 1) * sizeof(char));
    infos_insert->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos_insert->passwd, "stegx");
    strcpy(passwd_save1, "stegx");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));    

    stegx_suggest_algo(infos_insert);
    stegx_choose_algo(infos_insert, STEGX_ALGO_EOF);
    stegx_insert(infos_insert);
    
    uint32_t hidden_length=infos_insert->hidden_length;

    if (infos_insert->host.host != NULL)
        fclose(infos_insert->host.host);
    if (infos_insert->res != NULL)
        fclose(infos_insert->res);
    free(infos_insert->hidden_name);
    free(infos_insert->passwd);
    free(infos_insert);
    free(stegx_propos_algos);
        
	info_s *infos_extract = malloc(sizeof(info_s));
    infos_extract->mode = STEGX_MODE_EXTRACT;
    infos_extract->host.host = fopen("res3_test_insert.bmp", "r");;
    infos_extract->res = fopen("res3_test_extract.bmp", "w");
    char *passwd_save2 = malloc((strlen("stegx") + 1) * sizeof(char));
    infos_extract->passwd = malloc((strlen("stegx") + 1) * sizeof(char));
    strcpy(infos_extract->passwd, "stegx");
    strcpy(passwd_save2, "stegx");
    
    stegx_check_compatibility(infos_extract);
    stegx_detect_algo(infos_extract);
	
	/*
	on compare l'algorithme, la méthode, la taille du fichier caché et 
	le nom du fichier caché
	*/
	int test=((infos_extract->algo==STEGX_ALGO_EOF)&&(infos_extract->method==STEGX_WITH_PASSWD)
		&&(infos_extract->hidden_length==hidden_length)&&(strcmp(infos_extract->hidden_name,hidden_name_write1)==0));
		
	if (hidden_name_write1 != NULL)
        free(hidden_name_write1);
    if (passwd_save1 != NULL)
        free(passwd_save1);
        
    if (infos_extract->host.host != NULL)
        fclose(infos_extract->host.host);
    if (infos_extract->res != NULL)
        fclose(infos_extract->res);
    free(infos_extract->hidden_name);
    free(infos_extract->passwd);
    free(infos_extract);
    free(stegx_propos_algos);

    assert_int_equal(test, 1);
}

void test_detect_algo_without_passwd(void **state)
{
    (void)state;
    info_s *infos_insert = malloc(sizeof(info_s));
    infos_insert->mode = STEGX_MODE_INSERT;
    infos_insert->algo = STEGX_ALGO_EOF;
    infos_insert->method = STEGX_WITHOUT_PASSWD;
    infos_insert->host.host = fopen("../../../env/test/test1.bmp", "r");
    infos_insert->host.type = BMP_COMPRESSED;
    infos_insert->res = fopen("res4_test_insert.bmp", "w");
    infos_insert->hidden_name = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    char *hidden_name_write1 = malloc((strlen("test2.bmp") + 1) * sizeof(char));
    strcpy(infos_insert->hidden_name, "test2.bmp");
    strcpy(hidden_name_write1, "test2.bmp");
    infos_insert->hidden = fopen("../../../env/test/test2.bmp", "r");
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));  

    stegx_suggest_algo(infos_insert);
    stegx_choose_algo(infos_insert, STEGX_ALGO_EOF);
    stegx_insert(infos_insert);
    
    uint32_t hidden_length=infos_insert->hidden_length;

    if (infos_insert->host.host != NULL)
        fclose(infos_insert->host.host);
    if (infos_insert->res != NULL)
        fclose(infos_insert->res);
    if (infos_insert->hidden_name != NULL)
        free(infos_insert->hidden_name);
    if (infos_insert != NULL)
        free(infos_insert);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);
        
	info_s *infos_extract = malloc(sizeof(info_s));
    infos_extract->mode = STEGX_MODE_EXTRACT;
    infos_extract->host.host = fopen("res4_test_insert.bmp", "r");;
    infos_extract->res = fopen("res4_test_extract.bmp", "w");
    char *passwd_save2 = malloc((strlen("stegx") + 1) * sizeof(char));
    
    stegx_check_compatibility(infos_extract);
    stegx_detect_algo(infos_extract);
	
	/*
	on compare l'algorithme, la méthode, la taille du fichier caché et 
	le nom du fichier caché
	*/
	int test=((infos_extract->algo==STEGX_ALGO_EOF)&&(infos_extract->method==STEGX_WITHOUT_PASSWD)
		&&(infos_extract->hidden_length==hidden_length)&&(strcmp(infos_extract->hidden_name,hidden_name_write1)==0));
		
	if (hidden_name_write1 != NULL)
        free(hidden_name_write1);
        
    if (infos_extract->host.host != NULL)
        fclose(infos_extract->host.host);
    if (infos_extract->res != NULL)
        fclose(infos_extract->res);
    if (infos_extract->hidden_name != NULL)
        free(infos_extract->hidden_name);
    if (infos_extract != NULL)
        free(infos_extract);
    if (stegx_propos_algos != NULL)
        free(stegx_propos_algos);

    assert_int_equal(test, 1);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest check_compatibility_tests[] = {
	
    cmocka_unit_test(test_detect_algo_with_passwd),
    cmocka_unit_test(test_detect_algo_without_passwd),

};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(check_compatibility_tests, NULL, NULL);
}
