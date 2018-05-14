#ifndef LSB_H
#define LSB_H

#include <stdio.h>

#include "common.h"

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme LSB. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme a bien ete inseré ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 */
int insert_lsb(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme LSB. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme a bien ete extrait ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 */
int extract_lsb(info_s * infos);

#endif
