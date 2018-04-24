#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

type_e stegx_test_file_bmp(FILE* file){
	int i;
	uint32_t compress;
	uint16_t sig;
	if(file==NULL) return UNKNOWN;
	fseek(file,0,SEEK_SET);
	int read=fread(&sig, sizeof(uint16_t), 1, file);
	if(sig!=SIG_BMP){
		return UNKNOWN;
	}
	int move=fseek(file,ADDRESS_BMP_COMPRESS,SEEK_SET);
	if(move==-1){
		printf("erreur");
	}
	
	read=fread(&compress, sizeof(uint32_t), 1, file);
	if(compress==0) return BMP_UNCOMPRESSED;
	else return BMP_COMPRESSED;
}
