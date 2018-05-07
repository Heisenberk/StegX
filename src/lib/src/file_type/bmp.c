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
    assert(file);
    if (fseek(file, 0, SEEK_SET) == -1)
        return UNKNOWN;
    // lecture de la signature BMP
    uint16_t sig_read;
    if (fread(&sig_read, sizeof(uint16_t), 1, file) != 1)
        return UNKNOWN;
    if (sig_read != SIG_BMP) {
        return UNKNOWN;
    }

	if (fseek(file, ADDRESS_BMP_COMPRESS, SEEK_SET) == -1)
        return UNKNOWN;
    // lecture pour déterminer si c'est compressé ou non
    uint32_t compress;
    if (fread(&compress, sizeof(uint32_t), 1, file) != 1)
        return UNKNOWN;
    if (compress == 0) {
        return BMP_UNCOMPRESSED;
    } else {
        return BMP_COMPRESSED;
    }
}
