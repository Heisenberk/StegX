/** 
 * @file mp3.c
 * @brief Fichier MP3.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format MP3.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "mp3.h"

type_e stegx_test_file_mp3(FILE * file)
{
    assert(file);
    uint32_t sig = 0;
    if (fseek(file, 0, SEEK_SET) || (fread(&sig, sizeof(uint32_t), 1, file) != 1))
        return perror("MP3 test file: Can't read MP3 signature"), -1;
    return (sig & MASK_MP3_MPEGX_LAYER3) == SIG_MP3_MPEG1_LAYER3 || (sig & MASK_MP3_MPEGX_LAYER3) == SIG_MP3_MPEG2_LAYER3
        || (sig & MASK_MP3_ID3V2) == SIG_MP3_ID3V2 ? MP3 : UNKNOWN;
}
