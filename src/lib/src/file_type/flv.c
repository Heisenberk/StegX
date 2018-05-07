#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/**
 * \def Signature FLV
 * */
#define SIG_FLV 0x564C46

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant le type FLV, et si le format n'est pas 
 * reconnu : UNKNOWN. 
 */
type_e stegx_test_file_flv(FILE * file)
{
    assert(file);
    int i, read, move;
    move = fseek(file, 0, SEEK_SET);
    if (move == -1)
        return 1;
    // lecture de la signayure FLV
    uint32_t sig_read;
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if (read == 0)
        return 1;
    // on enleve 8 premiers bits car on soccupe des 3 derniers octets
    sig_read <<= 8;
    sig_read >>= 8;
    if (sig_read != SIG_FLV) {
        return UNKNOWN;
    }
    return FLV;
}

int insert_metadata_flv(info_s * infos)
{
    return 1;
}

int extract_metadata_flv(info_s * infos)
{
    return 1;
}
