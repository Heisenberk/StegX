/** 
 * @file wav.c
 * @brief Fichier WAVE.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format WAVE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "riff.h"

/** Signature d'un fichier WAVE. */
#define SIG_WAVE 0x45564157
/** Signautre d'un flux PCM. */
#define SIG_PCM 0x0001

/** Adresse (offset) de la signature du WAVE (octet). */
#define ADDRESS_WAV_WAVE 8
/** Adresse (offset) de la signature du PCM (octet). */
#define ADDRESS_WAV_PCM 20

type_e stegx_test_file_wav(FILE * file)
{
    assert(file);
    uint32_t sig_32;
    /* Lecture de la signature RIFF. */
    if (fseek(file, 0, SEEK_SET) == -1)
        return perror("Can't move to RIFF signature"), -1;
    if (fread(&sig_32, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read RIFF signature"), -1;
    if (sig_32 != SIG_RIFF)
        return UNKNOWN;

    /* Lecture de la singnature WAVE. */
    if (fseek(file, ADDRESS_WAV_WAVE, SEEK_SET) == -1)
        return perror("Can't move to WAVE signature"), -1;
    if (fread(&sig_32, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read WAVE signature"), -1;
    if (sig_32 != SIG_WAVE)
        return UNKNOWN;

    uint16_t sig_16;
    /* Lecture de la signature du PCM. */
    if (fseek(file, ADDRESS_WAV_PCM, SEEK_SET) == -1)
        return perror("Can't move to PCM signature"), -1;
    if (fread(&sig_16, sizeof(uint16_t), 1, file) != 1)
        return perror("Can't read PCM signature"), -1;

    if (sig_16 == SIG_PCM)
        return WAV_PCM;
    else
        return WAV_NO_PCM;
}

int insert_metadata_wav(info_s * infos)
{
    (void)infos;                /* Unused. */
    return 1;
}

int extract_metadata_wav(info_s * infos)
{
    (void)infos;                /* Unused. */
    return 1;
}
