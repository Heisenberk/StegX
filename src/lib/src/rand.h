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

