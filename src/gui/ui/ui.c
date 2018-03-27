/**
 * @file ui.c
 * @brief Gestion de l'interface utilisateur
 * @details Gère l'interface utilisateur. Appel les différentes fonctions
 * permettants de construire l'interface utilisateur et contient la structure de
 * l'interface.
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include "struct.h"
#include "builder.h"

void ui_create(GtkWidget *window)
{
    /* Initialisation de la structure de l'interface. */
    struct ui ui;
    ui.window = window;

    /* Construction de l'interface. */
    ui_build(&ui);
    /* Configuration des signaux. */
}
