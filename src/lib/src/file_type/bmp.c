#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

#define SIG_BMP 0x424D
#define ADDRESS_BMP_COMPRESS 30

type_e stegx_test_file_bmp(FILE * file)
{
    int i;
    uint32_t compress;
    uint16_t sig;
    int read,move;

    if (file == NULL)
        return UNKNOWN;
    move=fseek(file, 0, SEEK_SET);
    if(move==-1){
		err_print(ERR_FSEEK);
		return 1;
	}
    uint16_t sig_read;
    read = fread(&sig_read, sizeof(uint16_t), 1, file);
    if(read==0){
		err_print(ERR_READ);
		return 1;
	}
    sig = htobe16(sig_read);
    if (sig != SIG_BMP) {
        return UNKNOWN;
    }

    move = fseek(file, ADDRESS_BMP_COMPRESS, SEEK_SET);
    if (move == -1) {
		err_print(ERR_FSEEK);
		return 1;
    }

    read = fread(&compress, sizeof(uint32_t), 1, file);
    if (compress == 0) {
        return BMP_UNCOMPRESSED;
    } else {
        return BMP_COMPRESSED;
    }
}
