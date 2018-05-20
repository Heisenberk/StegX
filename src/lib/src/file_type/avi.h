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
 * @author Claire Baskevitch et Tristan Bessac
 */
struct avi {
};

/** Type du format AVI. */
typedef struct avi avi_s;

/**
 * @brief Test si le fichier est un fichier AVI.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{AVI_UNCOMPRESSED}, \r{AVI_COMPRESSED}, \r{UNKNOWN} ou -1 en 
 * cas d'erreur. 
 * @author Clément Caumes, Claire Baskevitch et Tristan Bessac
 */
type_e stegx_test_file_avi(FILE * file);

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme Metadata 
 * dans le format AVI. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si les données ont bien été inserées ; sinon 1 en cas d'erreur.
 * @author Claire Baskevitch et Tristan Bessac
 */
int insert_metadata_avi(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme Metadata
 * dans le formar AVI. 
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si les données ont bien été extraites ; sinon 1 en cas d'erreur.
 * @author Claire Baskevitch et Tristan Bessac
 */
int extract_metadata_avi(info_s * infos);

#endif
