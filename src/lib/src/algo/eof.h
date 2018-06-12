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
 * @file eof.h
 * @brief Algorithme EOF.
 * @details Contient les fonctions concernant l'algorithme EOF.
 */

#ifndef EOF_H
#define EOF_H

#include <stdio.h>

#include "common.h"

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme EOF. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme a bien ete inseré ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 * @author Clément Caumes et Pierre Ayoub
 */
int insert_eof(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme EOF. 
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si l'algorithme a bien ete extrait ; sinon 1 en cas d'erreur et met à jour
 * \r{stegx_errno}.
 * @author Clément Caumes et Pierre Ayoub
 */
int extract_eof(info_s * infos);

#endif
