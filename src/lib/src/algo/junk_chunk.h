/** 
 * @file junk_chunk.h
 * @brief Algorithme JUNK CHUNK.
 * @details Contient les fonctions concernant l'algorithme JUNK CHUNK.
 */

#ifndef JUNK_CHUNK_H
#define JUNK_CHUNK_H

#include <stdio.h>

#include "common.h"

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme Junk Chunk. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme a bien ete inseré ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 * @author Claire Baskevitch et Tristan Bessac
 */
int insert_junk_chunk(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme Junk Chunk. 
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si l'algorithme a bien ete extrait ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 * @author Claire Baskevitch et Tristan Bessac
 */
int extract_junk_chunk(info_s * infos);
#endif
