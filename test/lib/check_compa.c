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

extern type_e check_file_format(FILE * file);

/* Tests */

void test_file_compatibility_v1(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test1.bmp","r");
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    stegx_check_compatibility(infos);
    type_e type=infos->host.type;
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(type, BMP_COMPRESSED);
}

void test_file_compatibility_v2(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test4.bmp","r");
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    stegx_check_compatibility(infos);
    type_e type=infos->host.type;
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(type, BMP_UNCOMPRESSED);
}

void test_file_compatibility_v3(void **state)
{
	(void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test8.png","r");
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    stegx_check_compatibility(infos);
    type_e type=infos->host.type;
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(type, PNG);
}

void test_file_compatibility_v4(void **state)
{   
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test10.wav","r");
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    stegx_check_compatibility(infos);
    type_e type=infos->host.type;
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(type, WAV_NO_PCM);
}

void test_file_compatibility_v5(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test12.mp3","r");
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    stegx_check_compatibility(infos);
    type_e type=infos->host.type;
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(type, MP3);
}

void test_file_compatibility_v6(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test13.flv","r");
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    stegx_check_compatibility(infos);
    type_e type=infos->host.type;
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(type, FLV);
}

void test_file_compatibility_v7(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test14.avi","r");
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    stegx_check_compatibility(infos);
    type_e type=infos->host.type;
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(type, AVI_UNCOMPRESSED);
}

void test_file_compatibility_v8(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test15.tex","r");
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    stegx_check_compatibility(infos);
    type_e type=infos->host.type;
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(type, UNKNOWN);
}

void test_file_compatibility_v9(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/inconnu","r");
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    stegx_check_compatibility(infos);
    type_e type=infos->host.type;
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(type, UNKNOWN);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest check_compatibility_tests[] = {

    // tests unitaires compatibility
    cmocka_unit_test(test_file_compatibility_v1),
    cmocka_unit_test(test_file_compatibility_v2),
    cmocka_unit_test(test_file_compatibility_v3),
    cmocka_unit_test(test_file_compatibility_v4),
    cmocka_unit_test(test_file_compatibility_v5),
    cmocka_unit_test(test_file_compatibility_v6),
    cmocka_unit_test(test_file_compatibility_v7),
    cmocka_unit_test(test_file_compatibility_v8),
    cmocka_unit_test(test_file_compatibility_v9),

};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(check_compatibility_tests, NULL, NULL);
}
