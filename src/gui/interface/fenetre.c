#include <stdlib.h>
#include <gtk/gtk.h>

void dessine_fenetre(GtkWidget *window)
{
    GtkWidget *vertical_box;
    GtkWidget *note_book;
    GtkWidget *pButton;
    GtkWidget *pTable;
	
	vertical_box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vertical_box);
    
    // Creation du GtkNotebook 
    note_book = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(vertical_box), note_book, TRUE, TRUE, 0);
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(note_book), GTK_POS_TOP);
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(note_book), TRUE);
    
    pTable=gtk_table_new(12,8,TRUE);
    //gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));
 
        GtkWidget *pLabel1;
        GtkWidget *pTabLabel1;
        gchar *sLabel1;
        gchar *sTabLabel1;
 
        //sLabel1 = g_strdup_printf("Je suis la dissimulation");
        sTabLabel1 = g_strdup_printf("Dissimulation");
 
        /* Creation des differents GtkLabel */
        pLabel1 = gtk_label_new(sLabel1);
        pTabLabel1 = gtk_label_new(sTabLabel1);
        
        ////////////
        GtkWidget* emplacement_fichier_hote;
    GtkWidget* emplacement_fichier_a_cacher;
    GtkWidget* emplacement_fichier_resultat;
    GtkWidget* mot_de_passe;
    GtkWidget* nom_fichier_resultat;
    GtkWidget *bouton_dissimuler;
    GtkWidget* proposition_algos;
    

    mot_de_passe = gtk_entry_new();
    bouton_dissimuler = gtk_button_new_with_label("Dissimuler");
    gtk_entry_set_visibility(GTK_ENTRY(mot_de_passe),FALSE);
    //gtk_box_pack_start(GTK_BOX(vertical_box), pEntry, TRUE, FALSE, 0);
    nom_fichier_resultat=gtk_entry_new();
    
    /*proposition_algos=gtk_combo_box_text_new();
    const char *distros[] = {"Select distribution", "Fedora", "Mint", "Suse"};
    int i;
    for (i = 0; i < 4; i++){
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (proposition_algos), distros[i]);
	}
	gtk_combo_box_set_active (GTK_COMBO_BOX (proposition_algos), 0);*/
    

    emplacement_fichier_hote = gtk_file_chooser_button_new (("Sélectionne le fichier hôte"),
                                        GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (emplacement_fichier_hote),"/user");
    
    emplacement_fichier_a_cacher = gtk_file_chooser_button_new (("Sélectionne le fichier à cacher"),
                                        GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (emplacement_fichier_hote),"/user");
    
    emplacement_fichier_resultat = gtk_file_chooser_button_new (("Sélectionne l'emplacement du résultat"),
                                        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (emplacement_fichier_hote),"/user");
  	
	GtkWidget* label_fichier_hote=gtk_label_new("Fichier hôte");
    GtkWidget* label_fichier_a_cacher=gtk_label_new("Fichier à cacher");
    GtkWidget* label_emplacement=gtk_label_new("Emplacement du fichier à créer");
    GtkWidget* label_mot_de_passe=gtk_label_new("Mot de Passe"); 
    GtkWidget* label_nom_resultat=gtk_label_new("Nom du fichier à créer");
    GtkWidget* label_algos=gtk_label_new("Algorithme(s) disponible(s)");
    
    // Insertion des boutons
    gtk_table_attach(GTK_TABLE(pTable), label_fichier_hote,
        1, 3, 1, 2,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0); 
    gtk_table_attach(GTK_TABLE(pTable), emplacement_fichier_hote,
        1, 3, 2, 3,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
        
        gtk_table_attach(GTK_TABLE(pTable), label_fichier_a_cacher,
        5, 7, 1, 2,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);        
    gtk_table_attach(GTK_TABLE(pTable), emplacement_fichier_a_cacher,
        5, 7, 2, 3,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);
        
        gtk_table_attach(GTK_TABLE(pTable), label_emplacement,
        1, 3, 5, 6,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);        
    gtk_table_attach(GTK_TABLE(pTable), emplacement_fichier_resultat,
        1, 3, 6, 7,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0);   

        gtk_table_attach(GTK_TABLE(pTable), label_mot_de_passe,
        5, 7, 5, 6,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0); 
        gtk_table_attach(GTK_TABLE(pTable), mot_de_passe,
        5, 7, 6, 7,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0); 
        
        gtk_table_attach(GTK_TABLE(pTable), label_nom_resultat,
        1, 3, 8, 9,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0); 
        gtk_table_attach(GTK_TABLE(pTable), nom_fichier_resultat,
        1, 3, 9, 10,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0); 
        
        /*gtk_table_attach(GTK_TABLE(pTable), label_algos,
        5, 7, 8, 9,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0); 
        gtk_table_attach(GTK_TABLE(pTable), proposition_algos,
        5, 7, 9, 10,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0); */

        
        gtk_table_attach(GTK_TABLE(pTable), bouton_dissimuler,
        3, 5, 11, 12,
        GTK_EXPAND | GTK_FILL, GTK_EXPAND,
        0, 0); 
        /////////////////
 
        /* Insertion de la page */
        gtk_notebook_append_page(GTK_NOTEBOOK(note_book), pTable, pTabLabel1);
 
        //g_free(sLabel1);
        //g_free(sTabLabel1);
        
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
        gtk_notebook_append_page(GTK_NOTEBOOK(note_book), pLabel2, pTabLabel2);
 
        //g_free(sLabel2);
        //g_free(sTabLabel2);
}
