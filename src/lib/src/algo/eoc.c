/** 
 * @file eoc.c
 * @brief Algorithme EOC.
 * @details Contient les fonctions concernant l'algorithme EOC.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/** 
 * @brief Convertit val lue en little endian en big endian. 
 * @param nb nombre a convertir.
 * @return renvoie un nombre compris entre 0x00 et 0xFFFFFFFF.
 */
uint32_t stegx_htobe32(uint32_t nb){
    nb = ((nb << 8) & 0xFF00FF00) | ((nb >> 8) & 0xFF00FF); 
    return (nb << 16) | (nb >> 16);
    
}

int insert_eoc(info_s * infos)
{
    (void)infos;                /* Unused. */
    return 1;
}

int extract_eoc(info_s * infos)
{
    (void)infos;                /* Unused. */
    return 1;
}
