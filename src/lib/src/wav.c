#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

type_e stegx_test_file_wav(FILE* file){
	if(file==NULL) return UNKNOWN;
	
	uint32_t sig1,sig2;
	int read;
	
	fseek(file,0,SEEK_SET);
	read=fread(&sig1,sizeof(uint32_t),1,file);
	fseek(file,ADDRESS_WAV_WAVE,SEEK_SET);
	read=fread(&sig2,sizeof(uint32_t),1,file);
	
	if((sig1==SIG_WAV_RIFF)&&(sig2==SIG_WAV_WAVE)){
		return WAV_PCM;
	}
	return UNKNOWN;
}
