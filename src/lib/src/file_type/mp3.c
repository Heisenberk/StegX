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

/** Signature du MP3 version ID3V1. */
#define SIG_MP3_ID3V1 0xFBFF
/** Signature du MP3 version ID3V2. */
#define SIG_MP3_ID3V2 0x334449

type_e stegx_test_file_mp3(FILE * file)
{
    assert(file);
    /* Lecture de la signature MP3 version ID3V1. */
    uint16_t sig_16;
    if (fseek(file, 0, SEEK_SET) == -1)
        return perror("Can't move to MP3 ID3V1 signature"), -1;
    if (fread(&sig_16, sizeof(uint16_t), 1, file) != 1)
        return perror("Can't read MP3 ID3V1 signature"), -1;
    if (sig_16 == SIG_MP3_ID3V1)
        return MP3;

    /* Lecture de la signature MP3 version ID3V2. */
    uint32_t sig_32;
    if (fseek(file, 0, SEEK_SET) == -1)
        return perror("Can't move to MP3 ID3V2 signature"), -1;
    if (fread(&sig_32, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read MP3 ID3V2 signature"), -1;
    /* Suppression du premier octet car on s'occupe uniquement des 3 derniers
       octets. */
    sig_32 &= 0x00FFFFFF;
    if (sig_32 == SIG_MP3_ID3V2)
        return MP3;
    else
        return UNKNOWN;
}
