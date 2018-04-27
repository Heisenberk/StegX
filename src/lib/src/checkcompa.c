#include <stdio.h>
#include <stdlib.h>

#include "checkcompa.h"


type_e check_file_format(FILE* file){
	type_e test_bmp=stegx_test_file_bmp(file);
	if(test_bmp!=UNKNOWN) return test_bmp;
	
	type_e test_png=stegx_test_file_png(file);
	if(test_png!=UNKNOWN) return test_png;
	
	type_e test_wav=stegx_test_file_wav(file);
	if(test_wav!=UNKNOWN) return test_wav;
	
	type_e test_mp3=stegx_test_file_mp3(file);
	if(test_mp3!=UNKNOWN) return test_mp3;
	
	type_e test_avi=stegx_test_file_avi(file);
	if(test_avi!=UNKNOWN) return test_avi;
	
	type_e test_flv=stegx_test_file_flv(file);
	if(test_flv!=UNKNOWN) return test_flv;

	return UNKNOWN;
}

int stegx_check_compatibility(info_s* infos){
	if(infos->host.host==NULL) return 1;
	type_e host_type=check_file_format(infos->host.host);
	infos->host.type=host_type;
	return 0;
}
