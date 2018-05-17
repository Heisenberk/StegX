/**
 * @file builder.c
 * @brief Construction des wigets et des structures
 * @details Construction de l'interface utilisateur gérant tout ce qui concerne
 * directement ce qui est affiché sur la fenêtre principale. Ne gère pas les
 * signaux, les interfactions et les entrées/sorties.
 */

#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>
#include "misc.h"
#include "struct.h"

/**
 * @brief Crée l'onglet de dissimulation
 * @details Construit et place les widgets de l'onglet dissimulation. Initialise
 * aussi les messages utilisés pendant les différentes étapes de l'insertion.
 * @param ins Pointeur vers une structure d'onglet de dissimulation vers
 * laquelle lier les widgets construits.
 */
static void ui_build_insert(struct ui_insert *ins)
{
    assert(ins->tab);
    /* Widgets pour le fichier hôte (sélection de fichier). */
    ins->file_orig_lbl = gtk_label_new("Fichier hôte");
    ins->file_orig_fc = gtk_file_chooser_button_new(("Sélectionner le fichier hôte"),
                                                    GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(ins->tab), ins->file_orig_lbl, 1, 1, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_orig_fc, ins->file_orig_lbl,
                            GTK_POS_BOTTOM, 1, 1);

    /* Widgets pour le fichier à cacher (sélection de fichier). */
    ins->file_to_hide_lbl = gtk_label_new("Fichier à cacher");
    ins->file_to_hide_fc = gtk_file_chooser_button_new(("Sélectionner le fichier à cacher"),
                                                       GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_to_hide_lbl, ins->file_orig_lbl,
                            GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->file_to_hide_fc, ins->file_orig_fc,
                            GTK_POS_RIGHT, 1, 1);

    /* Widgets pour le fichier de sortie (sélection de dossier). */
    ins->file_out_dir_lbl = gtk_label_new("Emplacement du fichier à créer");
    ins->file_out_dir_fc = gtk_file_chooser_button_new(("Sélectionner le dossier de sortie"),
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
    gtk_grid_attach(GTK_GRID(ins->tab), ins->algos_lbl, 1, 1, 2, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->algos_cb, ins->algos_lbl,
                            GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_no_show_all(ins->algos_lbl, TRUE);
    gtk_widget_set_no_show_all(ins->algos_cb, TRUE);

    /* Widgets pour le mot de passe (champ de texte). */
    ins->passwd_lbl = gtk_label_new("Mot de passe");
    ins->passwd_ent = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(ins->passwd_ent), FALSE);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->passwd_lbl,
                            ins->file_out_dir_fc, GTK_POS_BOTTOM, 2, 1);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->passwd_ent,
                            ins->passwd_lbl, GTK_POS_BOTTOM, 2, 1);

    /* Boutons. */
    ins->but_txt_anal = "Analyser";
    ins->but_txt_anal_proc = "Analyse en cours...";
    ins->but_txt_dissi = "Dissimuler";
    ins->but_txt_dissi_proc = "Dissimulation en cours...";
    ins->but_txt_reset = "Réinitialisation";
    ins->but_reset = gtk_button_new_with_label(ins->but_txt_reset);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->but_reset, ins->passwd_ent,
                            GTK_POS_BOTTOM, 1, 1);
    ins->but = gtk_button_new_with_label(ins->but_txt_anal);
    gtk_grid_attach_next_to(GTK_GRID(ins->tab), ins->but, ins->but_reset, GTK_POS_RIGHT, 1, 1);

    /* Dialogues. */
    ins->dial_anal_cond = "Un des paramètres requis n'a pas été rempli !\n\n"
        "Veuillez vérifier que le fichier hôte et le fichier à cacher ont bien "
        "été choisis, ainsi que le dossier et le nom du fichier de sortie.";
    ins->dial_anal_proc = "Analyse des fichiers en cours... \n\n" "Veuillez patienter.";
    ins->dial_anal_end = "Analyse du fichier hôte et du fichier à cacher "
        "terminée. \n\nVous pouvez désormais sélectionner l'algorithme à utiliser "
        "lors de la dissimulation dans le menu déroulant prévu à cet effet.";
    ins->dial_anal_err = "Erreur durant l'analyse du fichier hôte. \n\n"
        "Veuillez sélectionner un fichier compatible avec l'application.";
    ins->dial_dissi_cond = "Un des paramètres requis n'a pas été rempli ! \n\n"
        "Veuillez vérifier que l'algorithme de stéganographie à utilisé à été choisi.";
    ins->dial_dissi_proc = "Dissimulation des données en cours... \n\n" "Veuillez patienter.";
    ins->dial_dissi_end = "Dissimulation des données terminée avec succès.";
    ins->dial_dissi_err = "Erreur durant la dissimulation des données.";
}

/**
 * @brief Crée l'onglet d'extraction
 * @details Construit et place les widgets de l'onglet de l'extraction.
 * @param extr Pointeur vers une structure d'onglet d'extraction vers laquelle
 * lier les widgets construits.
 */
static void ui_build_extrac(struct ui_extrac *extr)
{
    assert(extr->tab);
    /* Widgets pour le fichier hôte (sélection de fichier). */
    extr->file_orig_lbl = gtk_label_new("Fichier hôte");
    extr->file_orig_fc = gtk_file_chooser_button_new(("Sélectionner le fichier hôte"),
                                                     GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(extr->tab), extr->file_orig_lbl, 1, 1, 2, 1);
    gtk_grid_attach_next_to(GTK_GRID(extr->tab), extr->file_orig_fc, extr->file_orig_lbl,
                            GTK_POS_BOTTOM, 2, 1);

    /* Widgets pour le fichier de sortie (sélection de dossier). */
    extr->file_out_dir_lbl = gtk_label_new("Emplacement du fichier à créer");
    extr->file_out_dir_fc = gtk_file_chooser_button_new(("Sélectionner le dossier de sortie"),
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

    /* Bouton pour lancer l'extraction (widget). */
    extr->but_txt = "Extraire";
    extr->but_txt_proc = "Extraction en cours...";
    extr->but = gtk_button_new_with_label(extr->but_txt);
    gtk_grid_attach_next_to(GTK_GRID(extr->tab), extr->but, extr->passwd_ent, GTK_POS_BOTTOM, 2, 1);

    /* Dialogues. */
    extr->dial_cond = "Un des paramètres requis n'a pas été rempli ! \n\n"
        "Veuillez vérifier que le fichier hôte et que le dossier du "
        "fichier à créer ont bien été choisis.";
    extr->dial_proc = "Extraction des données en cours... \n\n" "Veuillez patienter.";
    extr->dial_end = "Extraction des données terminée avec succès.";
    extr->dial_err = "Erreur durant l'extraction des données.";
}

/**
 * @brief Crée le menu utilisateur
 * @details Initialise le menu utilisateur et construit puis place les widgets
 * du menu.
 * @param menu Structure du menu vers laquelle lier les widgets construits.
 */
static void ui_build_menu(struct ui_menu *menu)
{
    /* Création du menu. */
    menu->bar = gtk_menu_bar_new();
    gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(menu->bar), GTK_PACK_DIRECTION_RTL);
    /* Création du bouton à propos. */
    menu->about = gtk_menu_item_new_with_label("À propos");
    gtk_container_add(GTK_CONTAINER(menu->bar), menu->about);
}

void ui_build(struct ui *ui)
{
    assert(ui->window);
    /* Conteneur proposant plusieurs onglets. */
    ui->tabs = gtk_notebook_new();
    gtk_notebook_popup_enable(GTK_NOTEBOOK(ui->tabs));

    /* Création et insertion de l'onglet dissimulation. */
    ui->insert.tab_title = gtk_label_new("Dissimulation");
    ui->insert.tab = ui_grid_init();
    ui_build_insert(&(ui->insert));
    gtk_notebook_append_page(GTK_NOTEBOOK(ui->tabs), ui->insert.tab, ui->insert.tab_title);

    /* Création et insertion de l'onglet extraction. */
    ui->extrac.tab_title = gtk_label_new("Extraction");
    ui->extrac.tab = ui_grid_init();
    ui_build_extrac(&(ui->extrac));
    gtk_notebook_append_page(GTK_NOTEBOOK(ui->tabs), ui->extrac.tab, ui->extrac.tab_title);

    /* Création du menu. */
    ui_build_menu(&(ui->menu));
    assert(ui->menu.bar);

    /* Conteneur principal de la fenêtre. */
    ui->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(ui->box), ui->menu.bar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(ui->box), ui->tabs, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(ui->window), ui->box);
}
