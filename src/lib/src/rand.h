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
 * Variable globale représentant la seed pour la suite pseudo aléatoire.
 */
unsigned int stegx_seed=0;

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

