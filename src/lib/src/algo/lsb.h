/** 
 * @file lsb.h
 * @brief Algorithme LSB.
 * @details Contient les fonctions concernant l'algorithme LSB.
 */

#ifndef LSB_H
#define LSB_H

#include <stdio.h>

#include "common.h"

/** 
 * @brief Cache les octets de data dans pixels selon l'algorithme de 
 * protection des données en LSB. 
 * @details Pour l'insertion, à partir du mot de passe, est créé un seed. 
 * Puis les octets contenus dans data seront mélangés dans des pixels 
 * aléatoires. Pour l'extraction, la seed va permettre de remettre dans 
 * le bon ordre les octets mélangés.
 * @param pixels Tableau d'octets representant les pixels.
 * @param pixels_length Taille du tableau pixels (correspond à la taille du 
 * bloc data). 
 * @param data Tableau d'octets representant les donnees a cacher.
 * @param data_length Taille du tableau data (correspond à la taille des
 * données a cacher).
 * @param passwd Mot de passe à partir duquel un seed sera créé pour la suite 
 * pseudo aleatoire nécessaire au mélange des octets de tab. 
 * @param mode Mode qui peut être \req{STEGX_STEGX_MODE_INSERT} ou 
 * \req{STEGX_MODE_EXTRACT}. 
 * @return 0 si le melange des donnees s'est bien passé ; 1 sinon .
 */
int protect_data_lsb(uint8_t * pixels, uint32_t pixels_length, uint8_t * data, uint32_t data_length,
                     char *passwd, mode_e mode);

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme LSB. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme a bien ete inseré ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 */
int insert_lsb(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme LSB. 
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si l'algorithme a bien ete extrait ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 */
int extract_lsb(info_s * infos);

#endif
