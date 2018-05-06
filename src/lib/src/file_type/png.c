#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/**
 * \def Signature PNG
 * */
#define SIG_PNG 0x0A1A0A0D474E5089

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant le type PNG, et si le format n'est pas 
 * reconnu : UNKNOWN. 
 */
type_e stegx_test_file_png(FILE * file)
{
    assert(file);
    int move, i, read;
    move = fseek(file, 0, SEEK_SET);
    if (move == -1)
        return 1;
    uint64_t sig_read;
    move = fseek(file, 0, SEEK_SET);
    if (move == -1)
        return 1;
    // lecture signature PNG
    read = fread(&sig_read, sizeof(uint64_t), 1, file);
    if (read == 0)
        return 1;
    if (sig_read != SIG_PNG) {
        return UNKNOWN;
    }
    return PNG;
}
