/** 
 * @file eoc.h
 * @brief Algorithme End Of Chunk (EOC).
 * @details Contient les fonctions concernant l'algorithme EOC.
 */
#ifndef EOC_H
#define EOC_H

#include <stdio.h>

#include "common.h"

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme EOC. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme a bien été inseré ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 * @author Claire Baskevitch et Tristan Bessac
 */
int insert_eoc(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme EOC. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme a bien ete extrait ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 * @author CLaire Baskevitch et Tristan Bessac
 */
int extract_eoc(info_s * infos);

#endif
