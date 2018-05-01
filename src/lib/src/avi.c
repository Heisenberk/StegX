#include <stdio.h>
#include <stdlib.h>

#include "avi.h"

type_e stegx_test_file_avi(FILE* file){
	if(file==NULL) return UNKNOWN;
	fseek(file,0,SEEK_SET);
	int i;
	uint8_t sig1,sig2;
	int read;
	uint8_t tab_sig_riff[4]={SIG_RIFF_1, SIG_RIFF_2, SIG_RIFF_3_4, SIG_RIFF_3_4};
	uint8_t tab_sig_avi[4]={SIG_AVI_1, SIG_AVI_2, SIG_AVI_3, SIG_AVI_4};
	
	for(i=0;i<4;i++){
		read=fread(&sig1,sizeof(uint8_t),1,file);
		if(sig1!=tab_sig_riff[i]){
			return UNKNOWN;
		}
	}
	fseek(file,ADDRESS_SIG_AVI,SEEK_SET);
	for(i=0;i<4;i++){
		read=fread(&sig2,sizeof(uint8_t),1,file);
		if(sig2!=tab_sig_avi[i]){
			return UNKNOWN;
		}
	}
	return AVI_UNCOMPRESSED;
}
