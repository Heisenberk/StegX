/**
 * @file sugg_algo.h
 * @brief Proposition des algorithmes.
 * @details Module qui contient les fonctions qui permettent de proposer et de
 * vérifier l'algorithme de stéganographie à utiliser, ainsi que la fonction de
 * lecture/d'analyse du fichier hôte.
 */

#ifndef SUGG_ALGOS_H
#define SUGG_ALGOS_H

#include "stegx_common.h"

/** 
 * @brief Remplit les informations du fichier hôte. 
 * @details Remplit les informations du fichier hôte en fonction du type de
 * fichier. Effectue la lecture des données pour remplir la structure. 
 * @sideeffect Initialise et rempli le champ \r{info_s.host.file_info}.
 * @req \r{info_s.host.host} doit être un fichier ouvert en lecture et
 * compatible avec l'application.
 * @error \r{ERR_SUGG_ALGOS} si la fonction est utilisé en mode extraction.
 * @error \r{ERR_CHOICE_ALGO} si l'algorithme choisi n'est pas disponible.
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si tout se passe bien, sinon 1 s'il y a une erreur. 
 */
int fill_host_info(info_s * infos);

#endif
