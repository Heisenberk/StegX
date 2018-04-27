#include <stdio.h>
#include <stdlib.h>

#include "mp3.h"

type_e stegx_test_file_mp3(FILE* file){
	if(file==NULL) return UNKNOWN;
	fseek(file,0,SEEK_SET);
	int i;
	uint8_t sig1;
	uint8_t sig2;
	int read;
	int test_idv1=1;
	

	uint8_t tab_sig_mp3idv1[4]={SIG_MP3_ID3V1_1, SIG_MP3_ID3V1_2};
	for(i=0;i<2;i++){
		read=fread(&sig1,sizeof(uint8_t),1,file);
		if(sig1!=tab_sig_mp3idv1[i]) {
			test_idv1=0;
		}
	}
	if(test_idv1==1) {
		// si on arrive ici alors il s'agit d'un MP3-ID3V1
		return MP3;
	}
	
	uint8_t tab_sig_mp3idv2[3]={SIG_MP3_ID3V2_1, SIG_MP3_ID3V2_2, SIG_MP3_ID3V2_3};
	fseek(file,0,SEEK_SET);
	for(i=0;i<3;i++){
		read=fread(&sig2,sizeof(uint8_t),1,file);
		if((tab_sig_mp3idv2[i]!=sig2)&&(test_idv1==0)){
			return UNKNOWN;
		}
	}
	// si on arrive ici alors il s'agit d'un MP3-ID3V2
	return MP3;
}
