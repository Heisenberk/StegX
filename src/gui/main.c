/**
 * @file main.c
 * @brief Programme principal
 * @details Coeur de l'interface graphique, gérant tout ce qui ne concerne pas
 * directement ce qui est affiché sur la fenêtre principale.
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
    
/**
 * @brief Signal d'activation
 * @details Signal de l'initialisation et lancement de la fenêtre principale.
 * @param app Pointeur vers l'application à laquelle est liée ce signal.
 * @param user_data Pointeur vers des données supplémentaires à traiter.
 */
static void activate(GtkApplication* app, gpointer user_data)
{
    /* Fenêtre principale. */
    GtkWidget *window;

    /* Initialisation de la fenêtre. */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "StegX");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
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
