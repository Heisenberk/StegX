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

void ui_create(GtkWidget *window, struct ui *ui)
{
    /* Initialisation de la structure de l'interface. */
    ui->window = window;
    /* Construction de l'interface. */
    ui_build(ui);
    /* Configuration des signaux. */
    ui_signal_init(ui);
}

struct ui* ui_init()
{
    return calloc(1, sizeof(struct ui));
}

void ui_delete(struct ui *ui)
{
    free(ui);
}
