/** 
 * @file bmp.h
 * @brief Fichier BMP.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format BMP.
 */

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
/** Taille maximale lors de l'insertion metadata dans le fichier BMP. */
#define BMP_METADATA_MAX 0xFFFFFFFF
/** Déplacement absolu à faire pour savoir si il s'agit d'un fichier 
 * compressé ou non. 
 * */
#define ADDRESS_BMP_COMPRESS 30

/**
 * @brief Structure du format BMP.
 * @internal Ne pas changer les deux premiers membres (ordre et type).
 */
struct bmp {
    uint32_t header_size; /*!< Taille du Header en octets. */
    uint32_t data_size; /*!< Taille du bloc Data en octets. */
    uint32_t pixel_length; /*!< Nombre de bits par pixels. */
    uint32_t pixel_number; /*!< Nombre de pixels dans l'image. */
};

/** Type du format BMP. */
typedef struct bmp bmp_s;

/**
 * @brief Test si le fichier est un fichier BMP.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{BMP_COMPRESSED}, \r{BMP_UNCOMPRESSED} \r{UNKNOWN}, -1 en cas d'erreur. 
 */
type_e stegx_test_file_bmp(FILE * file);

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme Metadata 
 * dans le format BMP. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si les données ont bien été inserées ; sinon 1 en cas d'erreur.
 */
int insert_metadata_bmp(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme Metadata
 * dans le formar BMP. 
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si les données ont bien été extraites ; sinon 1 en cas d'erreur.
 */
int extract_metadata_bmp(info_s * infos);

#endif
