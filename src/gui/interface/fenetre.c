#include <stdlib.h>
#include <gtk/gtk.h>

#define ALGO_NB 3

void dessine_fenetre(GtkWidget *window)
{
    /* Conteneur principal de la fenêtre proposant plusieurs onglets. */
    GtkWidget *tabs = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), tabs);

    /* Onglet de la dissimulation. */

    /* Grille contenant les widgets l'onglet. */
    GtkWidget *tab_dissi_title = gtk_label_new("Dissimulation");
    GtkWidget *tab_dissi = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(tab_dissi), 10);
    gtk_grid_set_row_homogeneous(GTK_GRID(tab_dissi), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(tab_dissi), 10);
    gtk_grid_set_column_homogeneous(GTK_GRID(tab_dissi), TRUE);
    gtk_widget_set_margin_bottom(tab_dissi, 20);
    gtk_widget_set_margin_top(tab_dissi, 20);
    gtk_widget_set_margin_start(tab_dissi, 20);
    gtk_widget_set_margin_end(tab_dissi, 20);

    /* Widgets. */

    GtkWidget* lbl_file_orig = gtk_label_new("Fichier hôte");
    GtkWidget* fc_file_orig = gtk_file_chooser_button_new (
            ("Sélectionner le fichier hôte"), GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(tab_dissi), lbl_file_orig, 1, 1, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), fc_file_orig, lbl_file_orig,
            GTK_POS_BOTTOM, 1, 1);

    GtkWidget* lbl_file_to_hide = gtk_label_new("Fichier à cacher");
    GtkWidget* fc_file_to_hide = gtk_file_chooser_button_new(
            ("Sélectionner le fichier à cacher"), GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), lbl_file_to_hide,
            lbl_file_orig, GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), fc_file_to_hide, fc_file_orig,
            GTK_POS_RIGHT, 1, 1);

    GtkWidget* lbl_file_out_dir = gtk_label_new(
            "Emplacement du fichier à créer");
    GtkWidget* fc_file_out_dir = gtk_file_chooser_button_new (
            ("Sélectionner le dossier de sortie"),
            GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), lbl_file_out_dir,
            fc_file_orig, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), fc_file_out_dir,
            lbl_file_out_dir, GTK_POS_BOTTOM, 1, 1);

    GtkWidget* lbl_file_out_name = gtk_label_new("Nom du fichier à créer");
    GtkWidget* ent_file_out = gtk_entry_new();
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), lbl_file_out_name,
            lbl_file_out_dir, GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), ent_file_out,
            lbl_file_out_name, GTK_POS_BOTTOM, 1, 1);

    GtkWidget* lbl_passwd = gtk_label_new("Mot de passe"); 
    GtkWidget* ent_passwd = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(ent_passwd), FALSE);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), lbl_passwd,
            fc_file_out_dir, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), ent_passwd,
            lbl_passwd, GTK_POS_BOTTOM, 1, 1);
 
    GtkWidget *lbl_algos = gtk_label_new("Algorithme(s) disponible(s)");
    GtkWidget *cb_algos = gtk_combo_box_text_new();
    const char *lst_algos[] = {"LSB", "EOF", "Metadonnées"};
    for (int i = 0; i < ALGO_NB; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(cb_algos),
                lst_algos[i]);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(cb_algos), 0);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), lbl_algos, lbl_passwd,
            GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), cb_algos, lbl_algos,
            GTK_POS_BOTTOM, 1, 1);
    
    GtkWidget *but_dissi = gtk_button_new_with_label("Dissimuler");
    gtk_grid_attach_next_to(GTK_GRID(tab_dissi), but_dissi, ent_passwd,
            GTK_POS_BOTTOM, 2, 1);

    /* Insertion de la page. */
    gtk_notebook_append_page(GTK_NOTEBOOK(tabs), tab_dissi, tab_dissi_title);

        
        ///////////////////////////////
        
        GtkWidget *pLabel2;
        GtkWidget *pTabLabel2;
        gchar *sLabel2;
        gchar *sTabLabel2;
 
        sLabel2 = g_strdup_printf("Je suis l'extraction");
        sTabLabel2 = g_strdup_printf("Extraction");
 
        /* Creation des differents GtkLabel */
        pLabel2 = gtk_label_new(sLabel2);
        pTabLabel2 = gtk_label_new(sTabLabel2);
 
        /* Insertion de la page */
        gtk_notebook_append_page(GTK_NOTEBOOK(tabs), pLabel2, pTabLabel2);
 
        //g_free(sLabel2);
        //g_free(sTabLabel2);
}
