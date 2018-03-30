/**
 * @file signals.c
 * @brief Configuration des signaux
 * @details Configure les signaux de l'interface utilisateur. Ne gère que les
 * signaux et les interfactions, ne concerne pas l'affichage statique.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <gtk/gtk.h>
#include "struct.h"

/** Nombre d'algorithme à proposer. */
#define ALGO_NB 3

/** Liste d'algorithmes proposés. */
const static char *algos_lst[] = {"LSB", "EOF", "Metadonnées"};

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

/** 
 * @brief Lancement de l'insertion
 * @details Lance l'insertion des données du fichier à cacher dans le fichier
 * hôte. Met à jour l'interface pendant l'insertion et lance le thread chargé de
 * de l'insertion.
 * @param widget Bouton qui lance le signal.
 * @param ui Structure de l'interface utilisateur.
 */
static void insert_dissi_start(GtkWidget *widget, struct ui *ui);

/** 
 * @brief Exécution de l'insertion
 * @details Exécute l'insertion des données du fichier à cacher dans le fichier
 * hôte. Met à jour la variable "ret" avec le code de retour de l'insertion.
 * @param data Structure de l'interface utilisateur.
 * @return gboolean Code indiquant de supprimer le thread.
 */
static gboolean insert_dissi_do(gpointer data);

/**
 * @brief Termine l'insertion
 * @details Récupère le code de retour de la fonction de la bibliothèque. Si
 * tout est ok, on on revient à l'état initial. Sinon, on reste à la même étape.
 * La fonction met à jours les widgets et affiche les messages de dialogue en
 * conséquence.
 * @param ui Structure de l'interface utilisateur.
 */
static void insert_dissi_end(struct ui *ui);

/**
 * @brief Réinitialisation
 * @details Réinitialisation de l'affichage des widgets dans l'onglet insertion
 * et revient dans l'état initial d'analyse.
 * @param widget Bouton qui lance le signal.
 * @param ui Structure de l'interface utilisateur.
 */
static void insert_reset(GtkWidget *widget, struct ui *ui);

static void insert_anal_start(GtkWidget *widget, struct ui *ui)
{
    /* Si les conditions nécéssaires ne sont pas remplies. */
    if (!(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_orig_fc)))
            || !(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_to_hide_fc)))) {
        ui->insert.dial = gtk_message_dialog_new(GTK_WINDOW(ui->window),
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_WARNING, GTK_BUTTONS_CANCEL, ui->insert.dial_anal_cond, NULL);
        gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
        gtk_widget_destroy(ui->insert.dial);
    }
    else {
        /* Création du dialogue à afficher. */
        ui->insert.dial = gtk_message_dialog_new(GTK_WINDOW(ui->window),
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, ui->insert.dial_anal_proc, NULL);
        /* Lancement du thread de travaille. */
        gdk_threads_add_idle(insert_anal_do, ui);
        /* On met à jour le texte du bouton et on affiche le dialogue précédemment créé. */
        gtk_button_set_label(GTK_BUTTON(widget), ui->insert.but_txt_anal_proc);
        gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
    }
}

static gboolean insert_anal_do(gpointer data)
{
    struct ui *ui = (struct ui *) data;
    /* Processing. */
    printf("Fichier hôte : %s\n",
            gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_orig_fc)));
    printf("Fichier à cacher : %s\n",
            gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_to_hide_fc)));
    for(int i = 0; i < 1000000000; i++) {ret = 0;}
    /* Suppression du dialogue en cours. */
    gtk_dialog_response(GTK_DIALOG(ui->insert.dial), 0);
    gtk_widget_destroy(ui->insert.dial);
    /* Fin du traitement puis suppression du thread. */
    insert_anal_end(ui);
    return G_SOURCE_REMOVE;
}

static void insert_anal_end(struct ui *ui)
{
    gchar *dial_msg = NULL;
    GtkMessageType dial_type = 0;
    GtkButtonsType dial_but = 0;
    /* Si l'anayse à réussie. */
    if (ret == 0) {
        dial_msg = ui->insert.dial_anal_end;
        dial_type = GTK_MESSAGE_INFO;
        dial_but = GTK_BUTTONS_OK;
        /* Mise à jour du bouton pour la dissimulation. */
        gtk_button_set_label(GTK_BUTTON(ui->insert.but), ui->insert.but_txt_dissi);
        /* Mise à jour du signal pour lancer la disimulation. */
        g_signal_handlers_disconnect_by_func(ui->insert.but, insert_anal_start, ui);
        g_signal_connect(ui->insert.but, "clicked", G_CALLBACK(insert_dissi_start), ui);
        /* Retire les widgets de sélection des fichiers d'entrés de
         * l'affichage. */
        gtk_widget_hide(ui->insert.file_orig_fc);
        gtk_widget_hide(ui->insert.file_orig_lbl);
        gtk_widget_hide(ui->insert.file_to_hide_fc);
        gtk_widget_hide(ui->insert.file_to_hide_lbl);
        /* Ajoute le choix de sélection de l'algorithme. */
        for (int i = 0; i < ALGO_NB; i++) {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ui->insert.algos_cb),
                    algos_lst[i]);
        }
        gtk_combo_box_set_active(GTK_COMBO_BOX(ui->insert.algos_cb), 0);
        gtk_widget_show(ui->insert.algos_lbl);
        gtk_widget_show(ui->insert.algos_cb);
    }
    /* Si l'analyse à échouée. */
    else {
        dial_msg = ui->insert.dial_anal_err;
        dial_type = GTK_MESSAGE_ERROR;
        dial_but = GTK_BUTTONS_CANCEL;
        /* Mise à jour du bouton pour relancer l'analyse. */
        gtk_button_set_label(GTK_BUTTON(ui->insert.but), ui->insert.but_txt_anal);
    }
    /* Affichage du dialogue de fin. */
    ui->insert.dial = gtk_message_dialog_new(GTK_WINDOW(ui->window),
            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
            dial_type, dial_but, dial_msg, NULL);
    gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
    gtk_widget_destroy(ui->insert.dial);
}

static void insert_dissi_start(GtkWidget *widget, struct ui *ui)
{
    /* Si les conditions nécéssaires ne sont pas remplies. */
    if (!gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_out_dir_fc))
            || !strcmp(gtk_entry_get_text(GTK_ENTRY(ui->insert.file_out_name_ent)), "")) {
        ui->insert.dial = gtk_message_dialog_new(GTK_WINDOW(ui->window),
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_WARNING, GTK_BUTTONS_CANCEL, ui->insert.dial_dissi_cond, NULL);
        gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
        gtk_widget_destroy(ui->insert.dial);
    }
    else {
        /* Création du dialogue à afficher. */
        ui->insert.dial = gtk_message_dialog_new(GTK_WINDOW(ui->window),
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, ui->insert.dial_dissi_proc, NULL);
        /* Lancement du thread de travaille. */
        gdk_threads_add_idle(insert_dissi_do, ui);
        /* On met à jour le texte du bouton et on affiche le dialogue précédemment créé . */
        gtk_button_set_label(GTK_BUTTON(widget), ui->insert.but_txt_dissi_proc);
        gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
    }
}

static gboolean insert_dissi_do(gpointer data)
{
    struct ui *ui = (struct ui *) data;
    /* Processing. */
    printf("Dossier du fichier à créer : %s\n",
            gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_out_dir_fc)));
    printf("Nom du fichier à créer : %s\n",
            gtk_entry_get_text(GTK_ENTRY(ui->insert.file_out_name_ent)));
    printf("Mot de passe : %s\n",
            gtk_entry_get_text(GTK_ENTRY(ui->insert.passwd_ent)));
    printf("Algorithme choisis : %s\n",
            algos_lst[gtk_combo_box_get_active(GTK_COMBO_BOX(ui->insert.algos_cb))]);
    for(int i = 0; i < 1000000000; i++) {ret = 1;}
    /* Suppression du dialogue en cours. */
    gtk_dialog_response(GTK_DIALOG(ui->insert.dial), 0);
    gtk_widget_destroy(ui->insert.dial);
    /* Fin du traitement puis suppression du thread. */
    insert_dissi_end(ui);
    return G_SOURCE_REMOVE;
}

static void insert_dissi_end(struct ui *ui)
{
    gchar *dial_msg = NULL;
    GtkMessageType dial_type = 0;
    GtkButtonsType dial_but = 0;
    /* Si l'insertion à réussie. */
    if (ret == 0) {
        dial_msg = ui->insert.dial_dissi_end;
        dial_type = GTK_MESSAGE_INFO;
        dial_but = GTK_BUTTONS_OK;
        insert_reset(NULL, ui);
    }
    /* Si l'insertion à échouée. */
    else {
        dial_msg = ui->insert.dial_dissi_err;
        dial_type = GTK_MESSAGE_ERROR;
        dial_but = GTK_BUTTONS_CANCEL;
        /* Mise à jour du bouton pour relancer l'insertion. */
        gtk_button_set_label(GTK_BUTTON(ui->insert.but),
                ui->insert.but_txt_dissi);
    }
    /* Affichage du dialogue de fin. */
    ui->insert.dial = gtk_message_dialog_new(GTK_WINDOW(ui->window),
            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
            dial_type, dial_but, dial_msg, NULL);
    gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
    gtk_widget_destroy(ui->insert.dial);
}

static void insert_reset(GtkWidget *widget, struct ui *ui)
{
    /* Ré-affiche les widgets de choix de fichiers d'entrés. */
    gtk_widget_show(ui->insert.file_orig_fc);
    gtk_widget_show(ui->insert.file_orig_lbl);
    gtk_widget_show(ui->insert.file_to_hide_fc);
    gtk_widget_show(ui->insert.file_to_hide_lbl);
    /* Cache le widget permettant de choisir l'algorithme. */
    gtk_widget_hide(ui->insert.algos_lbl);
    gtk_widget_hide(ui->insert.algos_cb);
    /* Re-configure le bon label du bouton. */
    gtk_button_set_label(GTK_BUTTON(ui->insert.but), ui->insert.but_txt_anal);
    /* Re-configure les signaux pour revenir dans l'état initial. */
    g_signal_connect(ui->insert.but, "clicked", G_CALLBACK(insert_anal_start), ui);
    g_signal_handlers_disconnect_by_func(ui->insert.but, insert_dissi_start, ui);
}

void ui_signal_init(struct ui *ui)
{
    g_signal_connect(ui->insert.but, "clicked", G_CALLBACK(insert_anal_start), ui);
    g_signal_connect(ui->insert.but_reset, "clicked", G_CALLBACK(insert_reset), ui);
}
