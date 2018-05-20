/**
 * @file insert.h
 * @brief Insertion des données cachées dans une copie de l'hôte.
 * @details Module qui contient la fonction d'insertion et la fonction
 * d'écriture de la signature.
 */

#ifndef INSERT_H
#define INSERT_H

#include "stegx_common.h"

/** 
 * @brief Ecrit la signature StegX. 
 * @details Ecrit l'algorithme et la méthode (1 octet), la taille du fichier 
 * caché (4 octets), la taille du nom du fichier caché (1 octet), le nom du 
 * fichier caché XORé avec le mot de passe (255 octets max), le mot de passe 
 * par défaut si l'utilisateur n'a pas choisi de mot de passe (64 octets).
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si la signature a bien ete écrite, 1 sinon.
 * @author Clément Caumes
 */
int write_signature(info_s * infos);

#endif
