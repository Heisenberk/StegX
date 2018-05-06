#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/**
 * \def Signature MP3 ID3V1
 * */
#define SIG_MP3_ID3V1 0xFBFF

/**
 * \def Signature MP3 ID3V2
 * */
#define SIG_MP3_ID3V2 0x334449

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant le type MP3, et si le format n'est pas 
 * reconnu : UNKNOWN. 
 */
type_e stegx_test_file_mp3(FILE * file)
{
    assert(file);
    int i, read, move;
    move = fseek(file, 0, SEEK_SET);
    if (move == -1)
        return 1;

    int test_idv1 = 1;

    // lecture signature (ID3V1)
    uint16_t sig_read1;
    read = fread(&sig_read1, sizeof(uint16_t), 1, file);
    if (read == 0)
        return 1;
    // conversion BIG ENDIAN en endian de la machine
    if (sig_read1 != SIG_MP3_ID3V1) {
        test_idv1 = 0;
    }
    if (test_idv1 == 1) {
        // si on arrive ici alors il s'agit d'un MP3-ID3V1
        return MP3;
    }

    move = fseek(file, 0, SEEK_SET);
    if (move == -1)
        return 1;
    // lecture signature (ID3V2)
    uint32_t sig_read2;
    read = fread(&sig_read2, sizeof(uint32_t), 1, file);
    if (read == 0)
        return 1;
    // on enleve 8 premiers bits car on soccupe des 3 derniers octets
    sig_read2 <<= 8;
    sig_read2 >>= 8;
    if ((sig_read2 != SIG_MP3_ID3V2) && (test_idv1 == 0)) {
        return UNKNOWN;
    }
    // si on arrive ici alors il s'agit d'un MP3-ID3V2
    return MP3;
}
