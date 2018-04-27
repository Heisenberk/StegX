#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

type_e stegx_test_file_wav(FILE* file){
	if(file==NULL) return UNKNOWN;
	fseek(file,0,SEEK_SET);
	int i;
	uint8_t sig1,sig2;
	int read;
	
	uint8_t tab_sig_riff[4]={SIG_RIFF_1, SIG_RIFF_2, SIG_RIFF_3_4, SIG_RIFF_3_4};
	uint8_t tab_sig_wave[4]={SIG_WAVE_1, SIG_WAVE_2, SIG_WAVE_3, SIG_WAVE_4};
	
	for(i=0;i<4;i++){
		read=fread(&sig1,sizeof(uint8_t),1,file);
		if(sig1!=tab_sig_riff[i]){
			return UNKNOWN;
		}
	}
	fseek(file,ADDRESS_WAV_WAVE,SEEK_SET);
	for(i=0;i<4;i++){
		read=fread(&sig2,sizeof(uint8_t),1,file);
		if(sig2!=tab_sig_wave[i]){ 
			return UNKNOWN;
		}
	}
	fseek(file,ADDRESS_WAV_PCM,SEEK_SET);
	uint8_t pcm1,pcm2;
	uint8_t pcm_read;
	for(i=0;i<2;i++){
		read=fread(&pcm_read,sizeof(uint8_t),1,file);
		if(i==0) pcm1=pcm_read;
		else pcm2=pcm_read;
	}
	if((pcm1==PCM_1)&&(pcm2==PCM_2)){
		return WAV_PCM;
	}
	else {
		return WAV_NO_PCM;
	}
}
