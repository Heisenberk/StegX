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
 * @file builder.h
 * @brief Construction des wigets et des structures
 * @details Construction de l'interface utilisateur gérant tout ce qui concerne
 * directement ce qui est affiché sur la fenêtre principale. Ne gère pas les
 * signaux, les interfactions et les entrées/sorties.
 */

#ifndef UI_BUILDER_H_
#define UI_BUILDER_H_

#include "struct.h"

/**
 * @brief Construit la fenêtre principale
 * @details Construit la fenêtre principale en ajoutant les conteneurs et les
 * widgets. Ne connecte aucun signal.
 * @param ui Pointeur vers la structure de l'interface utilisateur sur laquelle
 * il faut construire l'affichage.
 * @author Pierre Ayoub et Damien Delaunay
 */
void ui_build(struct ui *ui);

#endif                          /* UI_BUILDER_H_ */
