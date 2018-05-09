#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/** Signature BMP */
#define SIG_BMP 0x4D42

type_e stegx_test_file_bmp(FILE * file)
{
    assert(file);
    if (fseek(file, 0, SEEK_SET) == -1)
        return UNKNOWN;
    // lecture de la signature BMP
    uint16_t sig_read;
    if (fread(&sig_read, sizeof(uint16_t), 1, file) != 1)
        return UNKNOWN;
    if (sig_read != SIG_BMP) {
        return UNKNOWN;
    }

	if (fseek(file, ADDRESS_BMP_COMPRESS, SEEK_SET) == -1)
        return UNKNOWN;
    // lecture pour déterminer si c'est compressé ou non
    uint32_t compress;
    if (fread(&compress, sizeof(uint32_t), 1, file) != 1)
        return UNKNOWN;
    if (compress == 0) {
        return BMP_UNCOMPRESSED;
    } else {
        return BMP_COMPRESSED;
    }
}

int insert_metadata_bmp(info_s * infos)
{
    return 1;
}

int extract_metadata_bmp(info_s * infos)
{
    return 1;
}
