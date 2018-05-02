#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "riff.h"

/**
 * \def Signature WAV
 * */
#define SIG_WAVE 0x57415645

/**
 * \def Signature PCM
 * */
#define SIG_PCM 0x0100

/**
 * \def Déplacement absolu à faire pour lire la signature WAV
 * */
#define ADDRESS_WAV_WAVE 8

/**
 * \def Déplacement absolu à faire pour lire la signature PCM
 * */
#define ADDRESS_WAV_PCM 20

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant le type WAV_PCM, WAV_NO_PCM, 
 * et si le format n'est pas reconnu : UNKNOWN. 
 */
type_e stegx_test_file_wav(FILE * file)
{
    if (file == NULL)
        return UNKNOWN;
    int i, move, read;
    move = fseek(file, 0, SEEK_SET);
    if (move == -1) {
        err_print(ERR_FSEEK);
        return 1;
    }
    // lecture de la signature RIFF
    uint32_t sig_read, sig;
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if (read == 0) {
        err_print(ERR_READ);
        return 1;
    }
    // conversion BIG ENDIAN en endian de la machine
    sig = be32toh(sig_read);
    if (sig != SIG_RIFF) {
        return UNKNOWN;
    }

    move = fseek(file, ADDRESS_WAV_WAVE, SEEK_SET);
    if (move == -1) {
        err_print(ERR_FSEEK);
        return 1;
    }
    // lecture de la singnature WAV
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if (read == 0) {
        err_print(ERR_READ);
        return 1;
    }
    // conversion BIG ENDIAN en endian de la machine
    sig = be32toh(sig_read);
    if (sig != SIG_WAVE) {
        return UNKNOWN;
    }

    move = fseek(file, ADDRESS_WAV_PCM, SEEK_SET);
    if (move == -1) {
        err_print(ERR_FSEEK);
        return 1;
    }
    // lecture de la signature PCM
    uint16_t pcm_read;
    uint16_t pcm;
    read = fread(&pcm_read, sizeof(uint16_t), 1, file);
    if (read == 0) {
        err_print(ERR_READ);
        return 1;
    }
    // conversion BIG ENDIAN en endian de la machine
    pcm = be16toh(pcm_read);
    if (pcm == SIG_PCM) {
        return WAV_PCM;
    } else
        return WAV_NO_PCM;
}
