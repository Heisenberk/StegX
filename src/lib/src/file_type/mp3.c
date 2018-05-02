#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"

#define SIG_MP3_ID3V1 0xFFFB
#define SIG_MP3_ID3V2 0x494433

type_e stegx_test_file_mp3(FILE * file)
{
    if (file == NULL)
        return UNKNOWN;
    fseek(file, 0, SEEK_SET);
    int i;
    int read;
    int test_idv1 = 1;

    uint16_t sig_read1, sig1;
    read = fread(&sig_read1, sizeof(uint16_t), 1, file);
    sig1 = htobe16(sig_read1);
    if (sig1 != SIG_MP3_ID3V1) {
        test_idv1 = 0;
    }
    if (test_idv1 == 1) {
        // si on arrive ici alors il s'agit d'un MP3-ID3V1
        return MP3;
    }

    fseek(file, 0, SEEK_SET);
    uint32_t sig_read2, sig2;
    read = fread(&sig_read2, sizeof(uint32_t), 1, file);
    sig2 = htobe32(sig_read2);
    sig2 >>= 8;                 // on enleve 8 derniers bits car on soccupe des 3 premiers octets
    if ((sig2 != SIG_MP3_ID3V2) && (test_idv1 == 0)) {
        return UNKNOWN;
    }
    // si on arrive ici alors il s'agit d'un MP3-ID3V2
    return MP3;
}
