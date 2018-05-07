#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/**
 * \def Signature BMP
 * */
#define SIG_BMP 0x4D42

/**
 * \def Déplacement absolu à faire pour savoir si il s'agit d'un fichier 
 * compressé ou non. 
 * */
#define ADDRESS_BMP_COMPRESS 30

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant le type BMP_UNCOMPRESSED, BMP_COMPRESSED, 
 * et si le format n'est pas reconnu : UNKNOWN. 
 */
type_e stegx_test_file_bmp(FILE * file)
{
    uint32_t compress;
    int i, read, move;

    assert(file);
    move = fseek(file, 0, SEEK_SET);
    if (move == -1)
        return UNKNOWN;
    // lecture de la signature BMP
    uint16_t sig_read;
    read = fread(&sig_read, sizeof(uint16_t), 1, file);
    if (read == 0){
        return UNKNOWN;
	}
    if (sig_read != SIG_BMP) {
        return UNKNOWN;
    }

    move = fseek(file, ADDRESS_BMP_COMPRESS, SEEK_SET);
    if (move == -1)
        return UNKNOWN;
    // lecture pour déterminer si c'est compressé ou non
    read = fread(&compress, sizeof(uint32_t), 1, file);
    if (compress == 0) {
        return BMP_UNCOMPRESSED;
    } else {
        return BMP_COMPRESSED;
    }
}

int insert_metadata_bmp(info_s * infos)
{
    return 1;
}

int extract_metadata_bmp(info_s * infos)
{
    return 1;
}
