/**
 * @file ui.c
 * @brief Affichage de l'interface utilisateur
 * @details Affichage de l'interface utilisateur gérant tout ce qui concerne
 * directement ce qui est affiché sur la fenêtre principale. Ne gère que
 * l'affichage et ne concerne pas les signaux, les interfactions et les
 * entrées/sorties.
 */

#include <stdlib.h>
#include <gtk/gtk.h>

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
 * @param tab Pointeur vers un widget GTK+ sur lequel lier les widgets
 * construits.
 */
static void ui_dissi_populate(GtkWidget *tab)
{
    /* Widgets pour le fichier hôte (sélection de fichier). */
    GtkWidget* lbl_file_orig = gtk_label_new("Fichier hôte");
    GtkWidget* fc_file_orig = gtk_file_chooser_button_new (
            ("Sélectionner le fichier hôte"), GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(tab), lbl_file_orig, 1, 1, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab), fc_file_orig, lbl_file_orig,
            GTK_POS_BOTTOM, 1, 1);

    /* Widgets pour le fichier à cacher (sélection de fichier). */
    GtkWidget* lbl_file_to_hide = gtk_label_new("Fichier à cacher");
    GtkWidget* fc_file_to_hide = gtk_file_chooser_button_new(
            ("Sélectionner le fichier à cacher"), GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach_next_to(GTK_GRID(tab), lbl_file_to_hide,
            lbl_file_orig, GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab), fc_file_to_hide, fc_file_orig,
            GTK_POS_RIGHT, 1, 1);

    /* Widgets pour le fichier de sortie (sélection de dossier). */
    GtkWidget* lbl_file_out_dir = gtk_label_new(
            "Emplacement du fichier à créer");
    GtkWidget* fc_file_out_dir = gtk_file_chooser_button_new (
            ("Sélectionner le dossier de sortie"),
            GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    gtk_grid_attach_next_to(GTK_GRID(tab), lbl_file_out_dir,
            fc_file_orig, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab), fc_file_out_dir,
            lbl_file_out_dir, GTK_POS_BOTTOM, 1, 1);

    /* Widgets pour le fichier de sortie (champ de texte pour nom
     * du fichier). */
    GtkWidget* lbl_file_out_name = gtk_label_new("Nom du fichier à créer");
    GtkWidget* ent_file_out = gtk_entry_new();
    gtk_grid_attach_next_to(GTK_GRID(tab), lbl_file_out_name,
            lbl_file_out_dir, GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab), ent_file_out,
            lbl_file_out_name, GTK_POS_BOTTOM, 1, 1);

    /* Widgets pour la sélection des algorithmes (menu déroulant). */
    GtkWidget *lbl_algos = gtk_label_new("Algorithme(s) disponible(s)");
    GtkWidget *cb_algos = gtk_combo_box_text_new();
    const char *lst_algos[] = {"LSB", "EOF", "Metadonnées"};
    for (int i = 0; i < ALGO_NB; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(cb_algos),
                lst_algos[i]);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(cb_algos), 0);
    gtk_grid_attach_next_to(GTK_GRID(tab), lbl_algos, fc_file_out_dir,
            GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab), cb_algos, lbl_algos,
            GTK_POS_BOTTOM, 1, 1);

    /* Widgets pour le mot de passe (champ de texte). */
    GtkWidget* lbl_passwd = gtk_label_new("Mot de passe"); 
    GtkWidget* ent_passwd = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(ent_passwd), FALSE);
    gtk_grid_attach_next_to(GTK_GRID(tab), lbl_passwd,
            lbl_algos, GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab), ent_passwd,
            lbl_passwd, GTK_POS_BOTTOM, 1, 1);
    
    /* Widget pour lancer la dissimulation (widget). */
    GtkWidget *but_dissi = gtk_button_new_with_label("Dissimuler");
    gtk_grid_attach_next_to(GTK_GRID(tab), but_dissi, cb_algos,
            GTK_POS_BOTTOM, 2, 1);
}

void ui_populate(GtkWidget *window)
{
    /* Conteneur principal de la fenêtre proposant plusieurs onglets. */
    GtkWidget *tabs = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), tabs);

    /* Création et insertion de l'onglet dissimulation. */
    GtkWidget *tab_dissi_title = gtk_label_new("Dissimulation");
    GtkWidget *tab_dissi = ui_grid_init();
    ui_dissi_populate(tab_dissi);
    gtk_notebook_append_page(GTK_NOTEBOOK(tabs), tab_dissi, tab_dissi_title);

    /* Création et insertion de l'onglet extraction. */
    GtkWidget *tab_extrac_title = gtk_label_new("Extraction");
    GtkWidget *tab_extrac = ui_grid_init();
    ui_dissi_populate(tab_extrac);
    gtk_notebook_append_page(GTK_NOTEBOOK(tabs), tab_extrac, tab_extrac_title);
}
