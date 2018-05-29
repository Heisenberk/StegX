/**
 * @file rand.c
 * @brief Module qui s'occupe de l'aléatoire.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "rand.h"

/**
 * Variable globale représentant la seed pour la suite pseudo aléatoire.
 */
unsigned int stegx_seed=0;

unsigned int create_seed(const char *passwd)
{
    unsigned int srand_nb = 0;
    int j = 0;
    char carac = passwd[j];
    do {
        srand_nb = (srand_nb + carac) % UINT_MAX;
        j++;
        carac = passwd[j];
    } while (carac != '\0');
    return srand_nb;
}

void stegx_srand(unsigned int seed){
	stegx_seed=seed;
}

int stegx_rand(){
	stegx_seed=(1103515245*stegx_seed+12345)%UINT_MAX;
	return stegx_seed%INT_MAX;
}
