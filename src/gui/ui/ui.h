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
 * @file ui.h
 * @brief Gestion de l'interface utilisateur
 * @details Gère l'interface utilisateur. Appel les différentes fonctions
 * permettants de construire l'interface utilisateur et de gérer les
 * interactions.
 */

#ifndef UI_H_
#define UI_H_

/** Type de l'interface utilisateur. */
typedef struct ui ui_t;

/**
 * @brief Création de l'interface utilisateur
 * @details Permet de créer entièrement l'interface utilisateur sur une fenêtre
 * donnée. Construit les widgets et configure les signaux.
 * @param window Pointeur vers la fenêtre sur laquelle construire l'interface utilisateur.
 * @param ui Pointeur vers l'interface utilisateur à remplir.
 * @author Pierre Ayoub et Damien Delaunay
 */
void ui_create(GtkWidget * window, struct ui *ui);

/**
 * @brief Initialisation de l'interface utilisateur
 * @details Permet d'allouer la mémoire pour l'interface utilisateur.
 * @return Pointeur sur l'interface utilisateur prête à être construite.
 * @author Pierre Ayoub et Damien Delaunay
 */
ui_t *ui_init();

/**
 * @brief Suppression de l'interface utilisateur
 * @details Permet de désallouer la mémoire utilisée pour l'interface
 * utilisateur.
 * @author Pierre Ayoub et Damien Delaunay
 */
void ui_delete(ui_t * ui);

#endif                          /* UI_H_ */
