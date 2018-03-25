/**
 * @file main.c
 * @brief Programme principal
 * @details Coeur de l'interface graphique, gérant tout ce qui ne concerne pas
 * directement ce qui est affiché sur la fenêtre principale.
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "interface/fenetre.h"
    
/**
 * @brief Signal d'activation
 * @details Signal de l'initialisation et lancement de la fenêtre principale.
 * @param app Pointeur vers l'application à laquelle est liée ce signal.
 * @param user_data Pointeur vers des données supplémentaires à traiter.
 */
static void activate(GtkApplication* app, gpointer user_data)
{
    /* Initialisation de la fenêtre principale. */
    GtkWidget *window;
    window = gtk_application_window_new(app);

    /* Propriétés de la fenêtre principale. */
    gtk_window_set_title(GTK_WINDOW(window), "StegX");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(window),
            "../src/gui/pic/stegx-55x55.png", NULL); /* A REFAIRE. */

    /* GtkWidget *button = gtk_button_new_with_label("Hello World test"); */
    /* g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL); */
    /* g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), */
            /* window); */

    /* GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL); */
    /* gtk_container_add(GTK_CONTAINER(button_box), button); */
    /* gtk_container_add(GTK_CONTAINER(window), button_box); */

    dessine_fenetre(window);

    /* Affichage. */
    gtk_widget_show_all(window);
}

/**
 * @brief Initialisation de l'application.
 * @details Initialisation de l'application GTK+, puis passe la main au signal
 * "activate" censé initialiser la fenêtre.
 * @param argc Nombre d'arguments passés à l'application.
 * @param argv Tableau de chaîne de caractères contenant les arguments passés à
 * l'application.
 * @return Code de retour de l'application (0 si aucune erreur).
 */
int main(int argc, char **argv)
{
    /* Application principale et statut de retour. */
    GtkApplication *app;
    int ret;

    /* Initialisation de GTK+ et connection du signal "activate". */
    app = gtk_application_new("org.stegx.gui", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    /* Lancement puis fin du programme. */
    ret = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return ret;
}
