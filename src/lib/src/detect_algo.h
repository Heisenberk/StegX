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
 * @file detect_algo.h
 * @brief Module de détection de l'algorithme.
 * @details Lecture de la signature d'un fichier hôte.
 */

#ifndef DETECT_ALGO_H
#define DETECT_ALGO_H

/**
 * @brief Saute la signature.
 * @param f Pointeur sur le fichier ou faire le saut.
 * @param h Pointeur sur la chaîne de caractère du nom du fichier dans la
 * signature.
 * @param m Méthode de protection des données utilisé.
 * @return Valeur de "fseek".
 * @author Pierre Ayoub et Damien Delaunay
 */
int sig_fseek(FILE * f, char *h, method_e m);

#endif                          /* ifndef DETECT_ALGO_H */
