#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"

#define SIG_FLV 0x464C56

type_e stegx_test_file_flv(FILE * file)
{
    if (file == NULL)
        return UNKNOWN;
    fseek(file, 0, SEEK_SET);
    int i;
    int read;
    uint32_t sig_read, sig;
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    sig = htobe32(sig_read);
    sig >>= 8;                  // on enleve 8 derniers bits car on soccupe des 3 premiers octets
    if (sig != SIG_FLV) {
        return UNKNOWN;
    }
    return FLV;
}
