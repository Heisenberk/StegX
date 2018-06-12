/*
 * This file is part of the StegX project.
 * Copyright (C) 2018  StegX Team
 * 
 * StegX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
 * @author Clément Caumes et Yassin Doudouh (BMP et PNG), Pierre Ayoub et Damien 
 * Delaunay (MP3 et WAV), Claire Baskevitch et Tristan Bessac (AVI et FLV)
 */
int fill_host_info(info_s * infos);

#endif
