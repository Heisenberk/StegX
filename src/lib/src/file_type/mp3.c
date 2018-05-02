#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/**
 * \def Signature MP3 ID3V1
 * */
#define SIG_MP3_ID3V1 0xFFFB

/**
 * \def Signature MP3 ID3V2
 * */
#define SIG_MP3_ID3V2 0x494433

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant le type MP3, et si le format n'est pas 
 * reconnu : UNKNOWN. 
 */
type_e stegx_test_file_mp3(FILE * file)
{
    if (file == NULL)
        return UNKNOWN;
    int i, read, move;
    move = fseek(file, 0, SEEK_SET);
    if (move == -1) {
        err_print(ERR_FSEEK);
        return 1;
    }

    int test_idv1 = 1;

    // lecture signature (ID3V1)
    uint16_t sig_read1, sig1;
    read = fread(&sig_read1, sizeof(uint16_t), 1, file);
    if (read == 0) {
        err_print(ERR_READ);
        return 1;
    }
    // conversion BIG ENDIAN en endian de la machine
    sig1 = be16toh(sig_read1);
    if (sig1 != SIG_MP3_ID3V1) {
        test_idv1 = 0;
    }
    if (test_idv1 == 1) {
        // si on arrive ici alors il s'agit d'un MP3-ID3V1
        return MP3;
    }

    move = fseek(file, 0, SEEK_SET);
    if (move == -1) {
        err_print(ERR_FSEEK);
        return 1;
    }
    // lecture signature (ID3V2)
    uint32_t sig_read2, sig2;
    read = fread(&sig_read2, sizeof(uint32_t), 1, file);
    if (read == 0) {
        err_print(ERR_READ);
        return 1;
    }
    // conversion BIG ENDIAN en endian de la machine
    sig2 = be32toh(sig_read2);
    sig2 >>= 8;                 // on enleve 8 derniers bits car on soccupe des 3 premiers octets
    if ((sig2 != SIG_MP3_ID3V2) && (test_idv1 == 0)) {
        return UNKNOWN;
    }
    // si on arrive ici alors il s'agit d'un MP3-ID3V2
    return MP3;
}
