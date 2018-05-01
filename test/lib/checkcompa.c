/* Inclusions minimales. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <errno.h>
#include "cmocka.h"

/* Inclusions supplémentaires. */
#include "libsteg.h"

/* Tests */

void test_file_bmp_v1(void** state){
	// 16 bits R5 G6 B5
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test1.bmp","r");
	type_e test=stegx_test_file_bmp(f);
	//if(f!=NULL) fclose(f);
	assert_int_equal(test,BMP_COMPRESSED);
}

void test_file_bmp_v2(void** state){
	// 16 bits R5 G6 B5
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test2.bmp","r");
	type_e test=stegx_test_file_bmp(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,BMP_COMPRESSED);
}

void test_file_bmp_v3(void** state){
	// 16 bits R5 G6 B5
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test3.bmp","r");
	type_e test=stegx_test_file_bmp(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,BMP_COMPRESSED);
}

void test_file_bmp_v4(void** state){
	// 24 bits R8 G8 B8
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test4.bmp","r");
	type_e test=stegx_test_file_bmp(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,BMP_UNCOMPRESSED);
}

void test_file_bmp_v5(void** state){
	// 32 bits A8 R8 G8 B8
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test5.bmp","r");
	type_e test=stegx_test_file_bmp(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,BMP_COMPRESSED);
}

void test_file_bmp_v6(void** state){
	// 32 bits X8 R8 G8 B8
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test6.bmp","r");
	type_e test=stegx_test_file_bmp(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,BMP_COMPRESSED);
}

void test_file_bmp_v7(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/inexistant","r");
	type_e test=stegx_test_file_bmp(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_png_v1(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/inexistant","r");
	type_e test=stegx_test_file_png(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_png_v2(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/inexistant","r");
	type_e test=stegx_test_file_png(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_png_v3(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test8.png","r");
	type_e test=stegx_test_file_png(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,PNG);
}


void test_file_png_v4(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test9.png","r");
	type_e test=stegx_test_file_png(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,PNG);
}

void test_file_wav_v1(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/inexistant","r");
	type_e test=stegx_test_file_wav(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_wav_v2(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test10.wav","r");
	type_e test=stegx_test_file_wav(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,WAV_NO_PCM);
}

void test_file_wav_v3(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test11.wav","r");
	type_e test=stegx_test_file_wav(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,WAV_NO_PCM);
}

void test_file_mp3_v1(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test1.bmp","r");
	type_e test=stegx_test_file_mp3(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_mp3_v2(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/inconnu","r");
	type_e test=stegx_test_file_mp3(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_mp3_v3(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test7.mp3","r");
	type_e test=stegx_test_file_mp3(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,MP3);
}

void test_file_mp3_v4(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test12.mp3","r");
	type_e test=stegx_test_file_mp3(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,MP3);
}

void test_file_flv_v1(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/inconnu","r");
	type_e test=stegx_test_file_flv(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_flv_v2(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test1.bmp","r");
	type_e test=stegx_test_file_flv(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_flv_v3(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test13.flv","r");
	type_e test=stegx_test_file_flv(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,FLV);
}

void test_file_avi_v1(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test13.flv","r");
	type_e test=stegx_test_file_avi(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_avi_v2(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test14.avi","r");
	type_e test=stegx_test_file_avi(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,AVI_UNCOMPRESSED);
}

void test_file_compatibility_v1(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test1.bmp","r");
	type_e test=check_file_format(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,BMP_COMPRESSED);
}

void test_file_compatibility_v2(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test4.bmp","r");
	type_e test=check_file_format(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,BMP_UNCOMPRESSED);
}

void test_file_compatibility_v3(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test8.png","r");
	type_e test=check_file_format(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,PNG);
}

void test_file_compatibility_v4(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test10.wav","r");
	type_e test=check_file_format(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,WAV_NO_PCM);
}

void test_file_compatibility_v5(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test12.mp3","r");
	type_e test=check_file_format(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,MP3);
}

void test_file_compatibility_v6(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test13.flv","r");
	type_e test=check_file_format(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,FLV);
}

void test_file_compatibility_v7(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test14.avi","r");
	type_e test=check_file_format(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,AVI_UNCOMPRESSED);
}

void test_file_compatibility_v8(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/test15.tex","r");
	type_e test=check_file_format(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

void test_file_compatibility_v9(void** state){
	(void) state; /* Unused */
	FILE* f=fopen("../../../test/lib/files/inconnu","r");
	type_e test=check_file_format(f);
	if(f!=NULL) fclose(f);
	assert_int_equal(test,UNKNOWN);
}

/* Structure CMocka contenant la liste des tests. */
const struct CMUnitTest check_compatibility_tests[] = {
	
	// tests unitaires BMP
    cmocka_unit_test(test_file_bmp_v1),
    cmocka_unit_test(test_file_bmp_v2),
    cmocka_unit_test(test_file_bmp_v3),
    cmocka_unit_test(test_file_bmp_v4),
    cmocka_unit_test(test_file_bmp_v5),
    cmocka_unit_test(test_file_bmp_v6),
    cmocka_unit_test(test_file_bmp_v7),
    
    // tests unitaires PNG
    cmocka_unit_test(test_file_png_v1),
    cmocka_unit_test(test_file_png_v2),
    cmocka_unit_test(test_file_png_v3),
    cmocka_unit_test(test_file_png_v4),
    
    // tests unitaires WAV
    cmocka_unit_test(test_file_wav_v1),
    cmocka_unit_test(test_file_wav_v2),
    cmocka_unit_test(test_file_wav_v3),
    
    // tests unitaires MP3
    cmocka_unit_test(test_file_mp3_v1),
    cmocka_unit_test(test_file_mp3_v2),
    cmocka_unit_test(test_file_mp3_v3),
    cmocka_unit_test(test_file_mp3_v4),
    
    // tests unitaires FLV
    cmocka_unit_test(test_file_flv_v1),
    cmocka_unit_test(test_file_flv_v2),
    cmocka_unit_test(test_file_flv_v3),
    
    // tests unitaires AVI
    cmocka_unit_test(test_file_avi_v1),
    cmocka_unit_test(test_file_avi_v2),
    
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
