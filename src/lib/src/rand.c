/**
 * @file rand.c
 * @brief Module qui s'occupe de l'aléatoire.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "rand.h"

void stegx_srand(unsigned int seed){
	stegx_seed=seed;
}

int stegx_rand(){
	stegx_seed=(1103515245*stegx_seed+12345)%UINT_MAX;
	return stegx_seed%INT_MAX;
}
