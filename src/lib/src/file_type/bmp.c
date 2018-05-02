#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"

#define SIG_BMP 0x424D
#define ADDRESS_BMP_COMPRESS 30

type_e stegx_test_file_bmp(FILE * file)
{
    int i;
    uint32_t compress;
    uint16_t sig;
    int read;

    if (file == NULL)
        return UNKNOWN;
    fseek(file, 0, SEEK_SET);
    uint16_t sig_read;
    read = fread(&sig_read, sizeof(uint16_t), 1, file);
    sig = htobe16(sig_read);
    if (sig != SIG_BMP) {
        return UNKNOWN;
    }

    int move = fseek(file, ADDRESS_BMP_COMPRESS, SEEK_SET);
    if (move == -1) {
        printf("erreur");
    }

    read = fread(&compress, sizeof(uint32_t), 1, file);
    if (compress == 0) {
        return BMP_UNCOMPRESSED;
    } else {
        return BMP_COMPRESSED;
    }
}
