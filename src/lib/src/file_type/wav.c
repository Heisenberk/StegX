#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "riff.h"

/**
 * \def Signature WAV
 * */
#define SIG_WAVE 0x45564157

/**
 * \def Signature PCM
 * */
#define SIG_PCM 0x0001

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
    assert(file);
    int i, move, read;
    move = fseek(file, 0, SEEK_SET);
    if (move == -1)
        return 1;
    // lecture de la signature RIFF
    uint32_t sig_read;
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if (read == 0)
        return 1;
    if (sig_read != SIG_RIFF) {
        return UNKNOWN;
    }

    move = fseek(file, ADDRESS_WAV_WAVE, SEEK_SET);
    if (move == -1)
        return 1;
    // lecture de la singnature WAV
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if (read == 0)
        return 1;
    if (sig_read != SIG_WAVE) {
        return UNKNOWN;
    }

    move = fseek(file, ADDRESS_WAV_PCM, SEEK_SET);
    if (move == -1)
        return 1;
    // lecture de la signature PCM
    uint16_t pcm_read;
    read = fread(&pcm_read, sizeof(uint16_t), 1, file);
    if (read == 0)
        return 1;
    if (pcm_read == SIG_PCM) {
        return WAV_PCM;
    } else
        return WAV_NO_PCM;
}
