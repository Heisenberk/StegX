/** 
 * @file wav.h
 * @brief Fichier WAVE.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format WAVE.
 */

#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/** Signature du subchunk data. */
#define WAV_DATA_SIGN 0x61746164
/** Signature du subchunk fmt. */
#define WAV_FMT_SIGN 0x20746d66
/** Offset entre le champ situé après la taille du subchunk fmt et le nombre de bit
 * par sample. */
#define WAV_FMT_BPS_OFF 14
/** Adresse du premier subchunk (octet). */
#define WAV_SUBCHK1_ADDR 12

/**
 * @brief Structure du format WAVE.
 * @internal Ne pas changer les deux premiers membres (ordre et type).
 * @author Pierre Ayoub et Damien Delaunay
 */
struct wav {
    uint32_t header_size;       /*!< Offset du début du segment data (octet). */
    uint32_t data_size;         /*!< Taille des données (octet). */
    uint32_t chunk_size;        /*!< Taille de chaque sample (bit). */
};

/** Type du format WAVE. */
typedef struct wav wav_s;

/**
 * @brief Test si le fichier est un fichier WAVE.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{WAV_PCM}, \r{WAV_NO_PCM}, \r{UNKNOWN} ou -1 en cas d'erreur. 
 * @author Clément Caumes, Pierre Ayoub et Damien Delaunay
 */
type_e stegx_test_file_wav(FILE * file);

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme Metadata 
 * dans le format WAV. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si les données ont bien été inserées ; sinon 1 en cas d'erreur.
 * @author Pierre Ayoub et Damien Delaunay
 */
int insert_metadata_wav(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme Metadata
 * dans le formar WAV. 
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si les données ont bien été extraites ; sinon 1 en cas d'erreur.
 * @author Pierre Ayoub et Damien Delaunay
 */
int extract_metadata_wav(info_s * infos);

#endif
