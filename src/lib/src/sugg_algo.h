/** 
 * @file sugg_algo.h
 * @brief Module de proposition des algorithmes.
 * @details Contient les fonctions concernant la proposition des algorithmes
 * ainsi que la fonction privée pour lire le fichier hôte.
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
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si tout se passe bien, sinon 1 s'il y a une erreur. 
 */
int fill_host_info(info_s * infos);

#endif
