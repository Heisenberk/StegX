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
 * Variable globale au module signal. Contient le code de retour de la fonction
 * de traitement de la bibliothèque appellée par le thread créé.
 */
static int ret;

/** 
 * @brief Lancement de l'analyse
 * @details Lance l'analyse des fichiers entrés par l'utilisateur. Met à jour
 * l'interface pendant l'analyse et lance le thread chargé de l'analyse.
 * @param widget Bouton qui lance le signal.
 * @param ui Structure de l'interface utilisateur.
 */
static void insert_anal_start(GtkWidget *widget, struct ui *ui);

/** 
 * @brief Exécution de l'analyse
 * @details Exécute l'analyse des fichiers entrés par l'utilisateur. Met à jour
 * la variable "ret" avec le code de retour de l'analyse.
 * @param data Structure de l'interface utilisateur.
 * @return gboolean Code indiquant de supprimer le thread.
 */
static gboolean insert_anal_do(gpointer data);

/**
 * @brief Termine l'analyse
 * @details Récupère le code de retour de la fonction de la bibliothèque. Si
 * tout est ok, on passe à l'étape suivante. Sinon, on revient à la même étape.
 * La fonction met à jours les widgets et affiche les messages de dialogue en
 * conséquence.
 * @param ui Structure de l'interface utilisateur.
 */
static void insert_anal_end(struct ui *ui);

static void insert_dissi_start(GtkWidget *widget, struct ui *ui)
{
    printf("DISSI\n");
}

static void insert_anal_end(struct ui *ui)
{
    gchar *dial_msg = NULL;
    /* Si l'anayse à réussie. */
    if (ret == 0) {
        dial_msg = ui->insert.dial_anal_end;
        /* Mise à jour du bouton pour la dissimulation. */
        gtk_button_set_label(GTK_BUTTON(ui->insert.but), ui->insert.but_txt_dissi);
        /* Mise à jour du signal pour lancer la disimulation. */
        g_signal_handlers_disconnect_by_func(ui->insert.but, insert_anal_start, ui);
        g_signal_connect(ui->insert.but, "clicked", G_CALLBACK(insert_dissi_start), ui);
    }
    /* Si l'analyse à échouée. */
    else {
        dial_msg = ui->insert.dial_anal_err;
        /* Mise à jour du bouton pour relancer l'analyse. */
        gtk_button_set_label(GTK_BUTTON(ui->insert.but), ui->insert.but_txt_anal);
    }
    /* Affichage du dialogue de fin. */
    ui->insert.dial = gtk_message_dialog_new(GTK_WINDOW(ui->window),
            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO, GTK_BUTTONS_OK, dial_msg, NULL);
    gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
    gtk_widget_destroy(ui->insert.dial);
}

static gboolean insert_anal_do(gpointer data)
{
    struct ui *ui = (struct ui *) data;
    /* Processing. */
    for(int i = 0; i < 1000000000; i++) {ret = 0;}
    /* Suppression du dialogue en cours. */
    gtk_dialog_response(GTK_DIALOG(ui->insert.dial), 0);
    gtk_widget_destroy(ui->insert.dial);
    /* Fin du traitement puis suppression du thread. */
    insert_anal_end(ui);
    return G_SOURCE_REMOVE;
}

static void insert_anal_start(GtkWidget *widget, struct ui *ui)
{
    /* Création du dialogue à afficher. */
    ui->insert.dial = gtk_message_dialog_new(GTK_WINDOW(ui->window),
            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, ui->insert.dial_anal_proc, NULL);
    /* Lancement du thread de travaille. */
    gdk_threads_add_idle(insert_anal_do, ui);
    /* On met à jour le texte du bouton et on affiche le dialogue précédemment créé . */
    gtk_button_set_label(GTK_BUTTON(widget), ui->insert.but_txt_anal_proc);
    gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
}

void ui_signal_init(struct ui *ui)
{
    g_signal_connect(ui->insert.but, "clicked", G_CALLBACK(insert_anal_start), ui);
}
