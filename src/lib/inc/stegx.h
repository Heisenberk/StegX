/**
 * @file stegx.h
 * @brief Fonctions d'utilisations de la bibliothèque StegX.
 * @details Fichier contenant des fonctions publiques destinées à être utilisées
 * par les applications utilisant la bibliothèque.
 */

#ifndef STEGX_H
#define STEGX_H

#include "stegx_common.h"
#include "stegx_errors.h"

info_s *stegx_init(stegx_choices_s * choices);

void stegx_clear(info_s * infos);

int stegx_check_compatibility(info_s * infos);

int stegx_suggest_algo(info_s * infos);

int stegx_choose_algo(info_s * infos, algo_e algo_choosen);

int stegx_insert(info_s * infos);

#endif                          /* ifndef STEGX_H */
