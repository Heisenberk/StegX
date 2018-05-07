#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "riff.h"

/**
 * \def Signature AVI
 * */
#define SIG_AVI 0x20495641

/**
 * \def Déplacement absolu à faire pour lire la signature AVI
 * */
#define ADDRESS_SIG_AVI 8

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant le type AVI_UNCOMPRESSED, AVI_COMPRESSED, 
 * et si le format n'est pas reconnu : UNKNOWN. 
 */
type_e stegx_test_file_avi(FILE * file)
{
    assert(file);
    if (fseek(file, 0, SEEK_SET) == -1)
        return UNKNOWN;
    // lecture de la signature RIFF
    uint32_t sig_read;
    if (fread(&sig_read, sizeof(uint32_t), 1, file) != 1)
        return UNKNOWN;
    if (sig_read != SIG_RIFF) {
        return UNKNOWN;
    }
    if (fseek(file, ADDRESS_SIG_AVI, SEEK_SET) == -1)
        return UNKNOWN;
    // lecture de la signature AVI
    if (fread(&sig_read, sizeof(uint32_t), 1, file) != 1)
        return UNKNOWN;
    if (sig_read != SIG_AVI) {
        return UNKNOWN;
    }
    return AVI_UNCOMPRESSED;
}
