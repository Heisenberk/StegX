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
 * @file rand.h
 * @brief Module qui s'occupe de l'aléatoire.
 */

#ifndef RAND_H
#define RAND_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** 
 * @brief Cree un seed a partir d'un mot de passe. 
 * @param passwd Mot de passe a partir duquel on veut creer un seed.
 * @return unsigned int représentant le seed a creer. 
 * @author Pierre Ayoub
 */
unsigned int create_seed(const char *passwd);

/** 
 * @brief Initialise la seed de la suite pseudo aléatoire. 
 * @param seed nombre qui représentera la seed.
 * @author Clément Caumes
 */
void stegx_srand(unsigned int seed);

/** 
 * @brief Renvoie un entier pseudo-aléatoire. 
 * @return renvoie l'entier de la suite pseudo aléatoire.
 * @author Clément Caumes
 */
int stegx_rand();

#endif

