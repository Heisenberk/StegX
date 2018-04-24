#include <stdio.h>
#include <stdlib.h>

#include "mp3.h"

type_e stegx_test_file_mp3(FILE* file){
	if(file==NULL) return UNKNOWN;
	fseek(file,0,SEEK_SET);
	int i;
	uint16_t sig1;
	uint8_t sig2;
	int read;
	
	read=fread(&sig1,sizeof(uint16_t),1,file);
	if(sig1==SIG_MP3_ID3V1){
		return MP3;
	}
	uint8_t tab_sig_mp3[3]={SIG_MP3_ID3V2_1, SIG_MP3_ID3V2_2, SIG_MP3_ID3V2_3};
	fseek(file,0,SEEK_SET);
	for(i=0;i<3;i++){
		read=fread(&sig2,sizeof(uint8_t),1,file);
		if(tab_sig_mp3[i]!=sig2){
			return UNKNOWN;
		}
	}
	return MP3;
}
