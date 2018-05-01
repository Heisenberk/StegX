#include <stdio.h>
#include <stdlib.h>

#include "png.h"

type_e stegx_test_file_png(FILE* file){
	if(file==NULL) return UNKNOWN;
	fseek(file,0,SEEK_SET);
	int i;
	int read;
	uint64_t sig_read;
	uint64_t sig;
	fseek(file,0,SEEK_SET);

	read=fread(&sig_read,sizeof(uint64_t),1,file);
	sig=htobe64(sig_read);
	if(sig!=SIG_PNG){
		return UNKNOWN;
	}
	return PNG;
}
