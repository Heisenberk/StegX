/** 
 * @file avi.h
 * @brief Fichier AVI.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format AVI.
 */

#ifndef AVI_H
#define AVI_H

#include <stdio.h>

#include "common.h"

/**
 * @brief Structure du format AVI.
 */
struct avi {

};

/** Type du format AVI. */
typedef struct avi avi_s;

/**
 * @brief Test si le fichier est un fichier AVI.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{AVI_UNCOMPRESSED}, \r{AVI_COMPRESSED} ou \r{UNKNOWN}. 
 */
type_e stegx_test_file_avi(FILE * file);

int insert_metadata_avi(info_s * infos);

int extract_metadata_avi(info_s * infos);

#endif
