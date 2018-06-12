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
