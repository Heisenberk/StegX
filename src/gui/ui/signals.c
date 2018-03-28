/**
 * @file signals.c
 * @brief Configuration des signaux
 * @details Configure les signaux de l'interface utilisateur. Ne gère que les
 * signaux et les interfactions, ne concerne pas l'affichage statique.
 */

#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>
#include "struct.h"

/**
 * @brief Configure le signal d'insertion
 * @details Configure le signal d'insertion des données.
 * @param widget Pointeur vers le widget connecté à ce signal.
 * @param ui Pointeur vers la structure de l'onglet insertion qui contient
 * les informations.
 */
static void ui_signal_insert(GtkWidget *widget, struct ui_insert *ui)
{
    assert(ui->but_lbl_orig);
    assert(ui->but_lbl_proc);
    gtk_button_set_label(GTK_BUTTON(widget), ui->but_lbl_proc);
}

/**
 * @brief Configure le signal d'extraction
 * @details Configure le signal d'extraction des données.
 * @param widget Pointeur vers le widget connecté à ce signal.
 * @param ui Pointeur vers la structure de l'onglet insertion qui contient
 * les informations.
 */
static void ui_signal_extrac(GtkWidget *widget, struct ui_insert *ui)
{
    gtk_button_set_label(GTK_BUTTON(widget), "Extraction des données en cours...");
}

void ui_signal_connect(struct ui *ui)
{
    g_signal_connect(ui->insert.but, "clicked", G_CALLBACK(ui_signal_insert),
            &(ui->insert));
    g_signal_connect(ui->extrac.but, "clicked", G_CALLBACK(ui_signal_extrac),
            &(ui->extrac));
}
