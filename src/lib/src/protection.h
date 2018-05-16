/**
 * @file protection.c
 * @brief Algorithme de protection des données avec le mot de passe.
 */

#ifndef PROTECTION_H
#define PROTECTION_H

#include <string.h>
#include <stdint.h>
#include "stegx_common.h"
#include "stegx_errors.h"

/** Valeur du tableau done pour savoir si un élément n'a pas été vu. */
#define NOT_DONE 0
/** Valeur du tableau done pour savoir si un élément a été vu. */
#define DONE 1

/** Taille du fichier à partir duquel on utilise un XOR au lieu du 
 *  melange aleatoire des octets cachés.
 *  LSB -> nb d'octets pour les pixels et taille du fichier a cacher 
 *  METADATA/EOF -> taille du fichier a cacher */
#define LENGTH_FILE_MAX 150000

/** 
 * @brief Cree un seed a partir d'un mot de passe. 
 * @param passwd Mot de passe a partir duquel on veut creer un seed.
 * @return unsigned int représentant le seed a creer. 
 */
unsigned int create_seed(char *passwd);

/** 
 * @brief Fait le mélange ou réarrange les octets selon l'algorithme de 
 * protection des données. 
 * @details Pour l'insertion, à partir du mot de passe, est créé un seed. 
 * Puis les octets contenus dans tab seront mélangés. Pour l'extraction, 
 * la seed va permettre de remettre dans le bon ordre les octets mélangés.
 * @param tab Tableau d'octets à mélanger.
 * @param hidden_length Taille du tableau tab (correspond à la taille du 
 * fichier à cacher/à analyser). 
 * @param passwd Mot de passe à partir duquel un seed sera créé pour la suite 
 * pseudo aleatoire nécessaire au mélange des octets de tab. 
 * @param mode Mode qui peut être \req{STEGX_STEGX_MODE_INSERT} ou 
 * \req{STEGX_MODE_EXTRACT}. 
 * @return 0 si le melange des donnees s'est bien passé ; 1 sinon 
 */
int protect_data(uint8_t * tab, uint32_t hidden_length, char *passwd, mode_e mode);

#endif
