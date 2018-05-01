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
#include "common/config.h"
#include "struct.h"
#include "misc.h"

/** Nombre d'algorithme à proposer. */
#define ALGO_NB 3

/** Liste d'algorithmes proposés. */
const static char *algos_lst[] = {"LSB", "EOF", "Metadonnées"};

/**
 * Variable globale au module signal qui contient le code de retour de la fonction
 * de traitement de la bibliothèque appellée par le thread créé.
 */
static int ret;

/**
 * Variable globale au module signal qui contient le numéro de l'état de
 * l'interface graphique pour le module dissimulation. L'état correspond à si on
 * doit effectuer l'analyse (0) ou effectuer la dissmulation (1).
 */
static int insert_state = 0;

/** 
 * @brief Lancement de l'étape courante de l'onglet dissimulation
 * @details Lance l'analyse des fichiers entrés par l'utilisateur ou l'insertion
 * des données du fichier à cacher dans le fichier hôte. Met à jour l'interface
 * pendant le traitement et lance le thread chargé du traitement.
 * @param widget Bouton qui a émis le signal.
 * @param ui Structure de l'interface utilisateur.
 */
static void insert_start(GtkWidget *widget, struct ui *ui);

/** 
 * @brief Exécution de l'étape courante de l'onglet dissimulation
 * @details Exécute l'analyse des fichiers entrés par l'utilisateur ou
 * l'insertion des données du fichier caché dans le fichier hôte. Met à jour la
 * variable "ret" avec le code de retour du traitement.
 * @param data Structure de l'interface utilisateur.
 * @return gboolean Code indiquant de supprimer le thread.
 */
static gboolean insert_do(gpointer data);

/**
 * @brief Termine l'étape courante de l'onglet dissimulation
 * @details Récupère le code de retour de la fonction de la bibliothèque. Si
 * tout est ok, si on effectué l'analyse on passe à l'étape suivante ; si on à
 * effectué l'insertion on revient à l'état inital. Sinon, on revient à la même
 * étape. La fonction met à jours les widgets et affiche les messages de
 * dialogue en conséquence.
 * @param ui Structure de l'interface utilisateur.
 */
static void insert_end(struct ui *ui);

/**
 * @brief Réinitialisation de la dissimulation
 * @details Réinitialisation de l'affichage des widgets dans l'onglet insertion
 * et revient dans l'état initial d'analyse.
 * @param widget Bouton qui a émis le signal.
 * @param ui Structure de l'interface utilisateur.
 */
static void insert_reset(GtkWidget *widget, struct ui *ui);

/**
 * @brief Lancement de l'extraction
 * @details Lance l'extraction du fichier caché. Met à jour l'interface pendant
 * le traitement et lance le thread chargé de de l'extraction.
 * @param widget Bouton qui a émis le signal.
 * @param ui Structure de l'interface utilisateur.
 */
static void extrac_start(GtkWidget *widget, struct ui *ui);

/** 
 * @brief Exécution de l'extraction
 * @details Exécute l'extraction des données du fichier caché dans le fichier
 * hôte. Met à jour la variable "ret" avec le code de retour de l'extraction.
 * @param data Structure de l'interface utilisateur.
 * @return gboolean Code indiquant de supprimer le thread.
 */
static gboolean extrac_do(gpointer data);

/**
 * @brief Termine l'extraction
 * @details Récupère le code de retour de la fonction de la bibliothèque. La
 * fonction met à jours les widgets et affiche les messages de dialogue en
 * conséquence.
 * @param ui Structure de l'interface utilisateur.
 */
static void extrac_end(struct ui *ui);

static void insert_start(GtkWidget *widget, struct ui *ui)
{
    /* Test de la condition en fonction de l'état. */
    int cond = (insert_state == 0) ?
        gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_orig_fc))
            && gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_to_hide_fc)) :
        gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_out_dir_fc))
            && strcmp(gtk_entry_get_text(GTK_ENTRY(ui->insert.file_out_name_ent)), "");
    /* Si la condition est remplie. */
    if (cond) {
        /* Création du dialogue à afficher pour patienter. */
        gchar *msg = insert_state == 0 ? ui->insert.dial_anal_proc : ui->insert.dial_dissi_proc;
        ui->insert.dial = ui_msg_dial_new(ui->window, msg, UI_DIAL_INFO_WAIT);
        /* Lancement du thread de travaille. */
        gdk_threads_add_idle(insert_do, ui);
        /* On met à jour le texte du bouton et on affiche le dialogue. */
        gtk_button_set_label(GTK_BUTTON(widget), ui->insert.but_txt_dissi_proc);
        gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
    }
    else {
        /* Création du dialogue d'avertissement puis affichage. */
        gchar *msg = insert_state == 0 ? ui->insert.dial_anal_cond : ui->insert.dial_dissi_cond;
        ui->insert.dial = ui_msg_dial_new(ui->window, msg, UI_DIAL_WARN);
        gtk_dialog_run(GTK_DIALOG(ui->insert.dial));
        gtk_widget_destroy(ui->insert.dial);
    }
}

static gboolean insert_do(gpointer data)
{
    struct ui *ui = (struct ui *) data;
    /* Si on doit faire l'analyse. */
    if (insert_state == 0) {
        printf("Fichier hôte : %s\n",
                gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_orig_fc)));
        printf("Fichier à cacher : %s\n",
                gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_to_hide_fc)));
    }
    /* Si c'est la dissimulation. */
    else {
        printf("Dossier du fichier à créer : %s\n",
                gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->insert.file_out_dir_fc)));
        printf("Nom du fichier à créer : %s\n",
                gtk_entry_get_text(GTK_ENTRY(ui->insert.file_out_name_ent)));
        printf("Mot de passe : %s\n",
                gtk_entry_get_text(GTK_ENTRY(ui->insert.passwd_ent)));
        printf("Algorithme choisis : %s\n",
                algos_lst[gtk_combo_box_get_active(GTK_COMBO_BOX(ui->insert.algos_cb))]);
    }
    /* Traitement. */
    for(int i = 0; i < 1000000000; i++) {ret = 0;}
    /* Suppression du dialogue en cours. */
    gtk_dialog_response(GTK_DIALOG(ui->insert.dial), 0);
    gtk_widget_destroy(ui->insert.dial);
    /* Fin du traitement puis suppression du thread. */
    insert_end(ui);
    return G_SOURCE_REMOVE;
}

static void insert_end(struct ui *ui)
{
    /* Si le traitement à réussi. */
    if (!ret) {
        gchar *msg = (insert_state == 0) ? ui->insert.dial_anal_end : ui->insert.dial_dissi_end;
        ui->insert.dial = ui_msg_dial_new(ui->window, msg, UI_DIAL_INFO_OK);
        /* Si c'est l'analyse. */
        if (insert_state == 0) {
            /* Mise à jour du bouton pour la dissimulation. */
            gtk_button_set_label(GTK_BUTTON(ui->insert.but), ui->insert.but_txt_dissi);
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
        /* Si c'est l'insertion. */
        else
            insert_reset(NULL, ui);
        insert_state ^= 1;
    }
    /* Si le traitement à échoué. */
    else {
        gchar *msg = (insert_state == 0) ? ui->insert.dial_anal_err : ui->insert.dial_dissi_err;
        ui->insert.dial = ui_msg_dial_new(ui->window, msg, UI_DIAL_ERR);
        /* Mise à jour du bouton pour relancer le traitement. */
        gtk_button_set_label(GTK_BUTTON(ui->insert.but), insert_state == 0 ?
                ui->insert.but_txt_anal : ui->insert.but_txt_dissi);
    }
    /* Affichage du dialogue de fin. */
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
}

static void extrac_start(GtkWidget *widget, struct ui *ui)
{
    /* Si les conditions nécéssaires ne sont pas remplies. */
    if (!gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->extrac.file_out_dir_fc))
            || !gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->extrac.file_orig_fc))) {
        ui->extrac.dial = ui_msg_dial_new(ui->window, ui->extrac.dial_cond, UI_DIAL_WARN);
        gtk_dialog_run(GTK_DIALOG(ui->extrac.dial));
        gtk_widget_destroy(ui->extrac.dial);
    }
    else {
        /* Création du dialogue d'attente puis lancement du thread de travaille. */
        ui->extrac.dial = ui_msg_dial_new(ui->window, ui->extrac.dial_proc, UI_DIAL_INFO_WAIT);
        gdk_threads_add_idle(extrac_do, ui);
        /* On met à jour le texte du bouton et on affiche le dialogue précédemment créé. */
        gtk_button_set_label(GTK_BUTTON(widget), ui->extrac.but_txt_proc);
        gtk_dialog_run(GTK_DIALOG(ui->extrac.dial));
    }
}

static gboolean extrac_do(gpointer data)
{
    struct ui *ui = (struct ui *) data;
    /* Processing. */
    printf("Fichier hôte : %s\n",
            gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->extrac.file_orig_fc)));
    printf("Dossier du fichier résultant : %s\n",
            gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(ui->extrac.file_out_dir_fc)));
    printf("Mot de passe : %s\n",
            gtk_entry_get_text(GTK_ENTRY(ui->extrac.passwd_ent)));
    for(int i = 0; i < 1000000000; i++) {ret = 0;}
    /* Suppression du dialogue en cours. */
    gtk_dialog_response(GTK_DIALOG(ui->extrac.dial), 0);
    gtk_widget_destroy(ui->extrac.dial);
    /* Fin du traitement puis suppression du thread. */
    extrac_end(ui);
    return G_SOURCE_REMOVE;
}

static void extrac_end(struct ui *ui)
{
    /* Si l'extraction à réussie. */
    if (!ret)
        ui->extrac.dial = ui_msg_dial_new(ui->window, ui->extrac.dial_end, UI_DIAL_INFO_OK);
    /* Si l'extraction à échouée. */
    else
        ui->extrac.dial = ui_msg_dial_new(ui->window, ui->extrac.dial_err, UI_DIAL_ERR);
    /* Mise à jour du bouton pour relancer l'extraction. */
    gtk_button_set_label(GTK_BUTTON(ui->extrac.but), ui->extrac.but_txt);
    /* Affichage du dialogue de fin. */
    gtk_dialog_run(GTK_DIALOG(ui->extrac.dial));
    gtk_widget_destroy(ui->extrac.dial);
}

/**
 * @brief Affiche le dialogue "à propos"
 * @details Construit et affiche le dialogue d'informations "à propos".
 * @param widget Bouton qui a émis le signal.
 * @param ui Structure de l'interface utilisateur.
 */
static void about(GtkWidget *widget, struct ui *ui)
{
    /* Paramètres. */
    static const gchar *authors[] = {
        "AYOUB Pierre", "BASKEVITCH Claire", "BESSAC Tristan",
        "CAUMES Clément", "DELAUNAY Damien", "DOUDOUH Yassin",
        NULL};
    static const gchar *copyright = "© 2018 StegX Team";
    static const gchar *website = "https://github.com/Heisenberk/StegX";
    GdkPixbuf *logo = gdk_pixbuf_new_from_file(program_logo(), NULL);
    /* Initilisation et affichage. */
    gtk_show_about_dialog(GTK_WINDOW(ui->window),
            "authors", authors, "logo", logo,
            "license", program_license, "website", website,
            "comments", program_desc, "copyright", copyright,
            "version", program_ver, "program_name", program_name,
            NULL);
    gtk_menu_item_deselect(GTK_MENU_ITEM(widget));
}

void ui_signal_init(struct ui *ui)
{
    /* Signaux de l'onglet insertion. */
    g_signal_connect(ui->insert.but, "clicked", G_CALLBACK(insert_start), ui);
    g_signal_connect(ui->insert.but_reset, "clicked", G_CALLBACK(insert_reset), ui);
    /* Signaux de l'onglet extraction. */
    g_signal_connect(ui->extrac.but, "clicked", G_CALLBACK(extrac_start), ui);
    /* Signaux du menu utilisateur. */
    g_signal_connect(ui->menu.about, "select", G_CALLBACK(about), ui);
}
