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
    int i, read, move;
    move = fseek(file, 0, SEEK_SET);
    if (move == -1) {
        err_print(ERR_FSEEK);
        return 1;
    }
    // lecture de la signature RIFF
    uint32_t sig_read;
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if (read == 0) return 1;
    if (sig_read != SIG_RIFF) {
        return UNKNOWN;
    }
    move = fseek(file, ADDRESS_SIG_AVI, SEEK_SET);
    if (move == -1) return 1;
    // lecture de la signature AVI
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if (read == 0) return 1;
    if (sig_read != SIG_AVI) {
        return UNKNOWN;
    }
    return AVI_UNCOMPRESSED;
}
