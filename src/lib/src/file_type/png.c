#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

#define SIG_PNG 0x89504E470D0A1A0A

type_e stegx_test_file_png(FILE * file)
{
    if (file == NULL)
        return UNKNOWN;
    int move,i,read;
    move=fseek(file, 0, SEEK_SET);
    if(move==-1){
		err_print(ERR_FSEEK);
		return 1;
	}
    uint64_t sig_read;
    uint64_t sig;
    move=fseek(file, 0, SEEK_SET);
    if(move==-1){
		err_print(ERR_FSEEK);
		return 1;
	}

    read = fread(&sig_read, sizeof(uint64_t), 1, file);
    if(read==0){
		err_print(ERR_READ);
		return 1;
	}
    sig = htobe64(sig_read);
    if (sig != SIG_PNG) {
        return UNKNOWN;
    }
    return PNG;
}
