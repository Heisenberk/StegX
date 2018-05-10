#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "riff.h"

/** Signature d'un fichier AVI. */
#define SIG_AVI 0x20495641

/** Déplacement absolu à faire pour lire la signature AVI. */
#define ADDRESS_SIG_AVI 8

type_e stegx_test_file_avi(FILE * file)
{
    assert(file);
    if (fseek(file, 0, SEEK_SET) == -1)
        return perror("Can't move to RIFF signature"), -1;
    // lecture de la signature RIFF
    uint32_t sig_read;
    if (fread(&sig_read, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read RIFF signature"), -1;
    if (sig_read != SIG_RIFF) {
        return UNKNOWN;
    }
    if (fseek(file, ADDRESS_SIG_AVI, SEEK_SET) == -1)
        return perror("Can't move to AVI signature"), -1;
    // lecture de la signature AVI
    if (fread(&sig_read, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read AVI signature"), -1;
    if (sig_read != SIG_AVI) {
        return UNKNOWN;
    }
    return AVI_UNCOMPRESSED;
}

int insert_metadata_avi(info_s * infos)
{
    return 1;
}

int extract_metadata_avi(info_s * infos)
{
    return 1;
}
