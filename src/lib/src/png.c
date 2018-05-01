#include <stdio.h>
#include <stdlib.h>

#include "png.h"

type_e stegx_test_file_png(FILE* file){
	if(file==NULL) return UNKNOWN;
	fseek(file,0,SEEK_SET);
	int i;
	uint8_t sig;
	int read;
	
	uint8_t tab_sig_png[8]={SIG_PNG_1, SIG_PNG_2, SIG_PNG_3, SIG_PNG_4, 
		SIG_PNG_5, SIG_PNG_6, SIG_PNG_7, SIG_PNG_8};
	fseek(file,0,SEEK_SET);
	//89 50 4E 47 0D 0A 1A 0A
	for(i=0;i<8;i++){
		read=fread(&sig,sizeof(uint8_t),1,file);
		if(sig!=tab_sig_png[i]){
			return UNKNOWN;
		}
	}
	return PNG;
}
