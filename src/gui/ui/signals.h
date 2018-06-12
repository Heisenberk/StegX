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
 * @file signals.h
 * @brief Configuration des signaux
 * @details Configure les signaux de l'interface utilisateur. Ne gère que les
 * signaux et les interfactions, ne concerne pas l'affichage statique.
 */

#ifndef UI_SIGNALS_H_
#define UI_SIGNALS_H_

#include "struct.h"

/**
 * @brief Initialise les signaux
 * @details Connecte les signaux aux widgets de la fenêtre principale.
 * @param ui Pointeur vers la structure de l'interface utilisateur sur laquelle
 * il faut configurer les signaux.
 * @author Pierre Ayoub et Damien Delaunay
 */
void ui_signal_init(struct ui *ui);

#endif                          /* UI_SIGNALS_H_ */
