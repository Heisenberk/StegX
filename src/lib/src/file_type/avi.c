#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "riff.h"

#define SIG_AVI 0x41564920
#define ADDRESS_SIG_AVI 8

type_e stegx_test_file_avi(FILE * file)
{
    if (file == NULL)
        return UNKNOWN;
    int i,read,move;
    move=fseek(file, 0, SEEK_SET);
    if(move==-1){
		err_print(ERR_FSEEK);
		return 1;
	}
    
    uint32_t sig_read, sig;
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if(read==0){
		err_print(ERR_READ);
		return 1;
	}
    sig = htobe32(sig_read);
    if (sig != SIG_RIFF) {
        return UNKNOWN;
    }
    move=fseek(file, ADDRESS_SIG_AVI, SEEK_SET);
    if(move==-1){
		err_print(ERR_FSEEK);
		return 1;
	}
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if(read==0){
		err_print(ERR_READ);
		return 1;
	}
    sig = htobe32(sig_read);
    if (sig != SIG_AVI) {
        return UNKNOWN;
    }
    return AVI_UNCOMPRESSED;
}
