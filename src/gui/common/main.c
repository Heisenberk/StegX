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
 * @file main.c
 * @brief Programme principal
 * @details Coeur de l'interface graphique, gérant tout ce qui ne concerne pas
 * directement ce qui est affiché sur la fenêtre principale.
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "common/config.h"
#include "ui/ui.h"

/**
 * @brief Signal d'activation
 * @details Signal de l'initialisation et lancement de la fenêtre principale.
 * @param app Pointeur vers l'application à laquelle est liée ce signal.
 * @param ui Pointeur vers la structure de l'interface utilisateur à laquelle
 * sera liée l'application.
 * @author Pierre Ayoub et Damien Delaunay
 */
static void activate(GtkApplication * app, ui_t * ui)
{
    /* Initialisation de la fenêtre principale. */
    GtkWidget *window;
    window = gtk_application_window_new(app);

    /* Propriétés de la fenêtre principale. */
    gtk_window_set_title(GTK_WINDOW(window), "StegX");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    if (program_logo())
        gtk_window_set_icon_from_file(GTK_WINDOW(window), program_logo(), NULL);

    /* Construction de la fenêtre avec les widgets puis lancement de
     * l'affichage. */
    ui_create(window, ui);
    gtk_widget_show_all(window);
}

/**
 * @brief Initialisation de l'application.
 * @details Initialisation de l'application GTK+, puis passe la main au signal
 * "activate" censé initialiser la fenêtre.
 * @param argc Nombre d'arguments passés à l'application.
 * @param argv Tableau de chaîne de caractères contenant les arguments passés à
 * l'application.
 * @return Code de retour de l'application (0 si aucune erreur).
 * @author Pierre Ayoub et Damien Delaunay
 */
int main(int argc, char **argv)
{
    /* Application principale, structure de l'interface et statut de retour. */
    GtkApplication *app;
    ui_t *ui = ui_init();
    int ret;

    /* Initialisation de GTK+ et connection du signal "activate", puis lancement
     * du programme. */
    app = gtk_application_new("org.stegx.gui", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), ui);
    ret = g_application_run(G_APPLICATION(app), argc, argv);

    /* Libération de la mémoire, puis renvoie le code de retour de GTK+. */
    g_object_unref(app);
    ui_delete(ui);
    return ret;
}
