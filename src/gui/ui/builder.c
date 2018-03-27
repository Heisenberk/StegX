/**
 * @file builder.c
 * @brief Construction de l'interface utilisateur
 * @details Construction de l'interface utilisateur gérant tout ce qui concerne
 * directement ce qui est affiché sur la fenêtre principale de manière statique.
 * Ne gère pas les signaux, les interfactions et les entrées/sorties.
 */

#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>
#include "struct.h"

/** Nombre d'algorithme à proposer. */
#define ALGO_NB 3

/**
 * @brief Crée une grille
 * @details Crée un widget une grille et l'initialise avec les propriétés voulus
 * dans notre application.
 * @return GtkWidget Pointeur sur le widget.
 */
static GtkWidget* ui_grid_init()
{
    GtkWidget *tab = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(tab), 10);
    gtk_grid_set_row_homogeneous(GTK_GRID(tab), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(tab), 10);
    gtk_grid_set_column_homogeneous(GTK_GRID(tab), TRUE);
    gtk_widget_set_margin_bottom(tab, 20);
    gtk_widget_set_margin_top(tab, 20);
    gtk_widget_set_margin_start(tab, 20);
    gtk_widget_set_margin_end(tab, 20);
    return tab;
}

/**
 * @brief Crée l'onglet de dissimulation
 * @details Construit et place les widgets de l'onglet dissimulation.
 * @param ins Pointeur vers une structure d'onglet de dissimulation vers laquel
 * lier les widgets construits.
 */
static void ui_build_insert(struct ui_insert *ins)
{
    assert(ins->tab);
    /* Widgets pour le fichier hôte (sélection de fichier). */
    ins->file_orig_lbl = gtk_label_new("Fichier hôte");
    ins->file_orig_fc = gtk_file_chooser_button_new (
            ("Sélectionner le fichier hôte"), GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(ins->tab), ins->file_orig_lbl, 1, 1, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_orig_fc, ins->file_orig_lbl,
            GTK_POS_BOTTOM, 1, 1);

    /* Widgets pour le fichier à cacher (sélection de fichier). */
    ins->file_to_hide_lbl = gtk_label_new("Fichier à cacher");
    ins->file_to_hide_fc = gtk_file_chooser_button_new(
            ("Sélectionner le fichier à cacher"), GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_to_hide_lbl,
            ins->file_orig_lbl, GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_to_hide_fc, ins->file_orig_fc,
            GTK_POS_RIGHT, 1, 1);

    /* Widgets pour le fichier de sortie (sélection de dossier). */
    ins->file_out_dir_lbl = gtk_label_new(
            "Emplacement du fichier à créer");
    ins->file_out_dir_fc = gtk_file_chooser_button_new (
            ("Sélectionner le dossier de sortie"),
            GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_out_dir_lbl,
            ins->file_orig_fc, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_out_dir_fc,
            ins->file_out_dir_lbl, GTK_POS_BOTTOM, 1, 1);

    /* Widgets pour le fichier de sortie (champ de texte pour nom
     * du fichier). */
    ins->file_out_name_lbl = gtk_label_new("Nom du fichier à créer");
    ins->file_out_name_ent = gtk_entry_new();
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_out_name_lbl,
            ins->file_out_dir_lbl, GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_out_name_ent,
            ins->file_out_name_lbl, GTK_POS_BOTTOM, 1, 1);

    /* Widgets pour la sélection des algorithmes (menu déroulant). */
    ins->algos_lbl = gtk_label_new("Algorithme(s) disponible(s)");
    ins->algos_cb = gtk_combo_box_text_new();
    const char *algos_lst[] = {"LSB", "EOF", "Metadonnées"};
    for (int i = 0; i < ALGO_NB; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ins->algos_cb),
                algos_lst[i]);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(ins->algos_cb), 0);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->algos_lbl, ins->file_out_dir_fc,
            GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->algos_cb, ins->algos_lbl,
            GTK_POS_BOTTOM, 1, 1);

    /* Widgets pour le mot de passe (champ de texte). */
    ins->passwd_lbl = gtk_label_new("Mot de passe"); 
    ins->passwd_ent = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(ins->passwd_ent), FALSE);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->passwd_lbl,
            ins->algos_lbl, GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->passwd_ent,
            ins->passwd_lbl, GTK_POS_BOTTOM, 1, 1);
    
    /* Widget pour lancer la dissimulation (widget). */
    ins->but = gtk_button_new_with_label("Dissimuler");
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->but, ins->algos_cb,
            GTK_POS_BOTTOM, 2, 1);
}

/**
 * @brief Crée l'onglet d'extraction
 * @details Construit et place les widgets de l'onglet de l'extraction.
 * @param extr Pointeur vers une structure d'onglet d'extraction vers laquel
 * lier les widgets construits.
 */
static void ui_build_extrac(struct ui_extrac *extr)
{
    assert(extr->tab);
    /* Widgets pour le fichier hôte (sélection de fichier). */
    extr->file_orig_lbl = gtk_label_new("Fichier hôte");
    extr->file_orig_fc = gtk_file_chooser_button_new (
            ("Sélectionner le fichier hôte"), GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(extr->tab), extr->file_orig_lbl, 1, 1, 2, 1);
    gtk_grid_attach_next_to(GTK_GRID(extr->tab), extr->file_orig_fc, extr->file_orig_lbl,
            GTK_POS_BOTTOM, 2, 1);

    /* Widgets pour le fichier de sortie (sélection de dossier). */
    extr->file_out_dir_lbl = gtk_label_new(
            "Emplacement du fichier à créer");
    extr->file_out_dir_fc = gtk_file_chooser_button_new (
            ("Sélectionner le dossier de sortie"),
            GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    gtk_grid_attach_next_to(GTK_GRID(extr->tab), extr->file_out_dir_lbl,
            extr->file_orig_fc, GTK_POS_BOTTOM, 2, 1);
    gtk_grid_attach_next_to(GTK_GRID(extr->tab), extr->file_out_dir_fc,
            extr->file_out_dir_lbl, GTK_POS_BOTTOM, 2, 1);

    /* Widgets pour le mot de passe (champ de texte). */
    extr->passwd_lbl = gtk_label_new("Mot de passe");
    extr->passwd_ent = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(extr->passwd_ent), FALSE);
    gtk_grid_attach_next_to(GTK_GRID(extr->tab), extr->passwd_lbl,
            extr->file_out_dir_fc, GTK_POS_BOTTOM, 2, 1);
    gtk_grid_attach_next_to(GTK_GRID(extr->tab), extr->passwd_ent,
            extr->passwd_lbl, GTK_POS_BOTTOM, 2, 1);

    /* Widget pour lancer l'extraction (widget). */
    extr->but = gtk_button_new_with_label("Extraire");
    gtk_grid_attach_next_to(GTK_GRID(extr->tab), extr->but, extr->passwd_ent,
            GTK_POS_BOTTOM, 2, 1);
}

/**
 * @brief Crée l'onglet d'information
 * @details Construit et place les widgets de l'onglet d'information.
 * @param abt Pointeur vers une structure d'onglet d'information vers laquel
 * lier les widgets construits.
 */
static void ui_build_about(struct ui_about *abt)
{
    assert(abt->tab);
    abt->info_lbl = gtk_label_new("Auteurs : \n"
            "- AYOUB Pierre \n"
            "- BASKEVITCH Claire \n"
            "- BESSAC Tristan \n"
            "- CAUMES Clément \n"
            "- BASKEVITCH Claire \n"
            "- DELAUNAY Damien \n"
            "- DOUDOUH Yassine \n\n"
            "Version : TODO \n"
            "Bibliothèque graphique : GTK+ 3 \n"
            "Bibliothèque de stéganographie : StegX \n"
            );
    gtk_grid_attach(GTK_GRID(abt->tab), abt->info_lbl, 1, 1, 1, 1);
}

void ui_build(struct ui *ui)
{
    assert(ui->window);
    /* Conteneur principal de la fenêtre proposant plusieurs onglets. */
    ui->tabs = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(ui->window), ui->tabs);

    /* Création et insertion de l'onglet dissimulation. */
    ui->insert.tab_title = gtk_label_new("Dissimulation");
    ui->insert.tab = ui_grid_init();
    ui_build_insert(&(ui->insert));
    gtk_notebook_append_page(GTK_NOTEBOOK(ui->tabs), ui->insert.tab,
            ui->insert.tab_title);

    /* Création et insertion de l'onglet extraction. */
    ui->extrac.tab_title = gtk_label_new("Extraction");
    ui->extrac.tab = ui_grid_init();
    ui_build_extrac(&(ui->extrac));
    gtk_notebook_append_page(GTK_NOTEBOOK(ui->tabs), ui->extrac.tab,
            ui->extrac.tab_title);

    /* Création et insertion de l'onglet d'information. */
    ui->about.tab_title = gtk_label_new("À propos");
    ui->about.tab = ui_grid_init();
    ui_build_about(&(ui->about));
    gtk_notebook_append_page(GTK_NOTEBOOK(ui->tabs), ui->about.tab,
            ui->about.tab_title);
}
