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
 * @file ui.c
 * @brief Gestion de l'interface utilisateur
 * @details Gère l'interface utilisateur. Appel les différentes fonctions
 * permettants de construire l'interface utilisateur et de gérer les
 * interactions.
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include "struct.h"
#include "builder.h"
#include "signals.h"

void ui_create(GtkWidget * window, struct ui *ui)
{
    /* Initialisation de la structure de l'interface. */
    ui->window = window;
    /* Construction de l'interface. */
    ui_build(ui);
    /* Configuration des signaux. */
    ui_signal_init(ui);
}

struct ui *ui_init()
{
    return calloc(1, sizeof(struct ui));
}

void ui_delete(struct ui *ui)
{
    free(ui);
}
