/** 
 * @file eof.h
 * @brief Algorithme EOF.
 * @details Contient les fonctions concernant l'algorithme EOF.
 */

#ifndef EOF_H
#define EOF_H

#include <stdio.h>

#include "common.h"

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme EOF. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme a bien ete inseré ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 * @author Clément Caumes
 */
int insert_eof(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme EOF. 
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si l'algorithme a bien ete extrait ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 * @author Clément Caumes
 */
int extract_eof(info_s * infos);

#endif
