#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

type_e stegx_test_file_bmp(FILE* file){
	int i;
	uint32_t compress;
	uint8_t sig;
	int read;
	
	if(file==NULL) return UNKNOWN;
	fseek(file,0,SEEK_SET);
	uint8_t tab_sig_bmp[2]={SIG_BMP_1, SIG_BMP_2};
	for(i=0;i<2;i++){
		read=fread(&sig, sizeof(uint8_t), 1, file);
		if(sig!=tab_sig_bmp[i]){
			return UNKNOWN;
		}
	}
	int move=fseek(file,ADDRESS_BMP_COMPRESS,SEEK_SET);
	if(move==-1){
		printf("erreur");
	}
	
	read=fread(&compress, sizeof(uint32_t), 1, file);
	if(compress==0){
		return BMP_UNCOMPRESSED;
	}
	else{
		return BMP_COMPRESSED;
	}
}


