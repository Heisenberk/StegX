#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/** Adresse (offset) de l'octet représentant le début de l'image (octet). */
#define BMP_DEF_PIC 10
/** Adresse (offset) de la taille du fichier (octet). */
#define BMP_DEF_LENGTH 2
/** Adresse (offset) de la taille des pixels (octet). */
#define BMP_DEF_PIX_LENGTH 28
/** Adresse (offset) du nombre de pixels dans l'image (octet). */
#define BMP_DEF_NB_PIXEL 18
/** Déplacement absolu à faire pour savoir si il s'agit d'un fichier 
 * compressé ou non. 
 * */
#define ADDRESS_BMP_COMPRESS 30


/** Structure du format BMP. */
struct bmp {
    uint32_t header_size;
    uint32_t data_size;
    uint32_t pixel_length;
    uint32_t pixel_number;
};

/** Type du format BMP. */
typedef struct bmp bmp_s;

/**
 * @brief Test si le fichier est un fichier BMP.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{BMP_COMPRESSED}, \r{BMP_UNCOMPRESSED} ou \r{UNKNOWN}. 
 */
type_e stegx_test_file_bmp(FILE * file);

int insert_metadata_bmp(info_s * infos);

int extract_metadata_bmp(info_s * infos);

#endif
