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
 * @file cli.h
 * @brief Traitement du lancement en ligne de commande
 * @details Traitement du lancement en ligne de commande vérifiant les paramètres rentrer par l'utilisateur.
 */

#ifndef CLI_H
#define CLI_H
#include "stegx_common.h"

/**
 * @brief Initialise la structure contenant les informations entrées en ligne de commande 
 * @return com la structure initialisée 
 * @author Claire Baskevitch et Tristan Bessac
 */
stegx_choices_s *init_stegx_info();

/**
 * @brief Remplie la structure avec les informations entrées en ligne de commande  
 * @details CRemplie la structure avec les informations entrées en ligne de commande grâce
 * à la fonction getopt_long 
 * @param com structure contenant les informations entrées en ligne de commande
 * @param argc nombre d'arguments entrés en ligne de commande
 * @param argv arguments entrés en ligne de commande
 * @author Claire Baskevitch et Tristan Bessac
 */
void fill_info(stegx_choices_s * com, const int argc, char *const *argv);

/**
 * @brief Affiche la présentation du projet
 * @details Affiche la présentation du projet.
 * @author Claire Baskevitch et Tristan Bessac
 */
void we_are_stegx();

/**
 * @brief Affiche l'aide
 * @details Affiche l'aide du lancement de l'application en ligne de commande et détail 
 * les différents paramètres à spécifier pour l'utilisateur.  
 * @author Claire Baskevitch et Tristan Bessac 
 */
void help();

/**
 * @brief Avertie l'utilisateur d'une erreur lors du lancement en ligne de commande
 * @details Avertie l'utilisateur d'une erreur lors du lancement en ligne de commande et
 * affiche l'aide. 
 * @author Claire Baskevitch et Tristan Bessac
 */
void unvalid_line(char *error_info);

/**
 * @brief Vérifie les informations entrés par l'utilisateur 
 * @details Vérifie que l'utilisateur a bien indiqué les informations nécessaires pour la dissimulation ou l'extraction
 * @author Claire Baskevitch et Tristan Bessac
 */
void check_info(stegx_choices_s * com);

/**
 * @brief libère la structure contenant les informations entrées en ligne de commande
 * @param com structure contenant les informations entrées en ligne de commande 
 * @author Claire Baskevitch et Tristan Bessac
 */
void dest_stegx_info(stegx_choices_s * com);

#endif
