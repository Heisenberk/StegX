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

/** 
 * @brief Cache les octets de data dans pixels selon l'algorithme de 
 * protection des données LSB pour BMP. 
 * @details Pour l'insertion, à partir du mot de passe, est créé un seed. 
 * Puis les octets contenus dans data seront mélangés dans des pixels 
 * aléatoires. Pour l'extraction, la seed va permettre de remettre dans 
 * le bon ordre les octets mélangés.
 * @param pixels Tableau d'octets representant les pixels.
 * @param pixels_length Taille du tableau pixels (correspond à la taille du 
 * bloc data dans BMP). 
 * @param data Tableau d'octets representant les donnees a cacher.
 * @param data_length Taille du tableau data (correspond à la taille des
 * données a cacher).
 * @param passwd Mot de passe à partir duquel un seed sera créé pour la suite 
 * pseudo aleatoire nécessaire au mélange des octets de tab. 
 * @param mode Mode qui peut être \req{STEGX_STEGX_MODE_INSERT} ou 
 * \req{STEGX_MODE_EXTRACT}. 
 * @return 0 si le melange des donnees s'est bien passé ; 1 sinon 
 */
int protect_data_lsb_bmp(uint8_t * pixels, uint32_t pixels_length, uint8_t * data,
                         uint32_t data_length, char *passwd, mode_e mode);

#endif
