#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/**
 * \def Signature FLV
 * */
#define SIG_FLV 0x464C56

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant le type FLV, et si le format n'est pas 
 * reconnu : UNKNOWN. 
 */
type_e stegx_test_file_flv(FILE * file)
{
    if (file == NULL)
        return UNKNOWN;
    int i, read, move;
    move = fseek(file, 0, SEEK_SET);
    if (move == -1) {
        err_print(ERR_FSEEK);
        return 1;
    }
    // lecture de la signayure FLV
    uint32_t sig_read, sig;
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    if (read == 0) {
        err_print(ERR_READ);
        return 1;
    }
    // conversion BIG ENDIAN en endian de la machine
    sig = be32toh(sig_read);
    sig >>= 8;                  // on enleve 8 derniers bits car on soccupe des 3 premiers octets
    if (sig != SIG_FLV) {
        return UNKNOWN;
    }
    return FLV;
}
