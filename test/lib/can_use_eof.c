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

/* Tests */

void test_can_use_eof_v1(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test1.bmp","r");
    infos->host.type=BMP_COMPRESSED;
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    int test=can_use_eof(infos);
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(test, 0);
}

void test_can_use_eof_v2(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test4.bmp","r");
    infos->host.type=BMP_UNCOMPRESSED;
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    int test=can_use_eof(infos);
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(test, 0);
}

void test_can_use_eof_v3(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/inexistant","r");
    infos->host.type=UNKNOWN;
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    int test=can_use_eof(infos);
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(test, 1);
}

void test_can_use_eof_v4(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test8.png","r");
    infos->host.type=PNG;
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    int test=can_use_eof(infos);
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(test, 0);
}

void test_can_use_eof_v5(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test10.wav","r");
    infos->host.type=WAV_NO_PCM;
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    int test=can_use_eof(infos);
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(test, 0);
}

void test_can_use_eof_v6(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test15.wav","r");
    infos->host.type=WAV_PCM;
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    int test=can_use_eof(infos);
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(test, 0);
}

void test_can_use_eof_v7(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test7.mp3","r");
    infos->host.type=WAV_PCM;
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    int test=can_use_eof(infos);
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(test, 0);
}

void test_can_use_eof_v8(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test14.avi","r");
    infos->host.type=AVI_UNCOMPRESSED;
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    int test=can_use_eof(infos);
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(test, 0);
}


void test_can_use_eof_v9(void **state)
{
    (void)state;             
    info_s* infos=malloc(sizeof(info_s));
    infos->mode=STEGX_MODE_INSERT;
    infos->algo=STEGX_ALGO_EOF;
    infos->method=STEGX_WITH_PASSWD;
    infos->host.host=fopen("../../../env/test/test13.flv","r");
    infos->host.type=FLV;
    infos->res=fopen("res.bmp","w");
    infos->hidden_name=malloc((strlen("test2.bmp")+1)*sizeof(char));
    strcpy(infos->hidden_name,"test2.bmp");
    infos->passwd=malloc((strlen("stegx")+1)*sizeof(char));
    strcpy(infos->passwd,"stegx");
    
    int test=can_use_eof(infos);
    
    if(infos->host.host!=NULL) fclose(infos->host.host);
    if(infos->res!=NULL) fclose(infos->res);
    if(infos->hidden_name!=NULL) free(infos->hidden_name);
    if(infos->passwd!=NULL) free(infos->passwd);
    if(infos!=NULL) free(infos);
    
    assert_int_equal(test, 0);
}


/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest suggest_algos_tests[] = {

    // tests unitaires compatibility
    cmocka_unit_test(test_can_use_eof_v1),
    cmocka_unit_test(test_can_use_eof_v2),
    cmocka_unit_test(test_can_use_eof_v3),
    cmocka_unit_test(test_can_use_eof_v4),
    cmocka_unit_test(test_can_use_eof_v5),
    cmocka_unit_test(test_can_use_eof_v6),
    cmocka_unit_test(test_can_use_eof_v7),
    cmocka_unit_test(test_can_use_eof_v8),
    cmocka_unit_test(test_can_use_eof_v9),

};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(suggest_algos_tests, NULL, NULL);
}
