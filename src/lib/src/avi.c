#include <stdio.h>
#include <stdlib.h>

#include "avi.h"

type_e stegx_test_file_avi(FILE* file){
	if(file==NULL) return UNKNOWN;
	fseek(file,0,SEEK_SET);
	int i;
	int read;
	
	uint32_t sig_read,sig;
	read=fread(&sig_read,sizeof(uint32_t),1,file);
	sig=htobe32(sig_read);
	if(sig!=SIG_RIFF){
		return UNKNOWN;
	}
	fseek(file,ADDRESS_SIG_AVI,SEEK_SET);
	read=fread(&sig_read,sizeof(uint32_t),1,file);
	sig=htobe32(sig_read);
	if(sig!=SIG_AVI){
		return UNKNOWN;
	}
	return AVI_UNCOMPRESSED;
}
