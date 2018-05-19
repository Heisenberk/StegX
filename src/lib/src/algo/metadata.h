/** 
 * @file metadata.h
 * @brief Algorithme METADATA.
 * @details Contient les fonctions concernant l'algorithme METADATA.
 */

#ifndef METADATA_H
#define METADATA_H

#include <stdio.h>

#include "common.h"

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme Metadata. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si les données ont bien été inserées ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 */
int insert_metadata(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme Metadata. 
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si les données ont bien été extraites ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 */
int extract_metadata(info_s * infos);

#endif
