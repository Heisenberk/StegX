/**
 * @file protection.h
 * @brief Algorithme de protection des données avec le mot de passe.
 * @details Module gérant la création d'une seed à partir d'un mot de passe et
 * l'algorithme de protection des données cachées.
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
#define LENGTH_FILE_MAX 50000

/** 
 * @brief Cree un seed a partir d'un mot de passe. 
 * @param passwd Mot de passe a partir duquel on veut creer un seed.
 * @return unsigned int représentant le seed a creer. 
 * @author Pierre Ayoub
 */
unsigned int create_seed(const char *passwd);

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
 * @return 0 si le melange des donnees s'est bien passé ; 1 sinon. 
 * @author Clément Caumes
 */
int protect_data(uint8_t * tab, uint32_t hidden_length, const char *passwd, mode_e mode);

/**
 * @brief Écrit des données XORées avec un mot de passe.
 * @internal Pas de gestion d'erreur dans la boucle car cela ralentit beaucoup.
 * Si tout à été bien fait avant, il ne devrait pas y avoir d'erreur !
 * @param src Fichier où lire la donnée.
 * @param res Fichier où écrire la donnée.
 * @param passwd Mot de passe utilisé pour générer la seed.
 * @return 0 si tout est ok, 1 s'il y a eu une erreur lors de la lecture du
 * fichier source.
 * @author Pierre Ayoub
 */
int data_xor_write_file(FILE * src, FILE * res, const char *passwd);

/**
 * @brief Écrit des données XORées avec un mot de passe.
 * @sideeffect Modifie le tableau src pour y écrire les données.
 * @param src Tableau où lire et écrire la donnée.
 * @param passwd Mot de passe utilisé pour générer la seed.
 * @param len Taille du tableau source.
 * @author Pierre Ayoub
 */
void data_xor_write_tab(uint8_t * src, const char *passwd, const uint32_t len);

/**
 * @brief Écrit des données mélangé ou remise en ordre avec un mot de passe.
 * @param src Fichier où lire la donnée.
 * @param res Fichier où écrire la donnée.
 * @param pass Mot de passe utilisé pour générer la seed.
 * @param len Longueur des données à cacher / cacher.
 * @param m Mode d'utilisation (insertion ou extraction).
 * @return 0 si tout est ok, 1 s'il y a eu une erreur.
 * @author Pierre Ayoub
 */
int data_scramble_write(FILE * src, FILE * res, const char *pass,
                        const uint32_t len, const mode_e m);

#endif
