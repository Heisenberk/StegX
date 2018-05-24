/**
 * @file misc.h
 * @brief Fonctions diverses pour GTK+
 * @details Contient des fonctions diverses utilisant les fonctions de GTK+ afin
 * de factoriser du code et d'avoir des raccourcis.
 */

#ifndef UI_MISC_H_
#define UI_MISC_H_

#include <gtk/gtk.h>

/** Nature du dialogue. */
enum ui_dial_type {
    UI_DIAL_INFO_OK,            /*!< Dialogue d'information que tout est ok. */
    UI_DIAL_INFO_WAIT,          /*!< Dialogue d'information pour patienter. */
    UI_DIAL_WARN,               /*!< Dialogue d'avertissement. */
    UI_DIAL_ERR                 /*!< Dialogue d'erreur. */
};

/**
 * @brief Crée une grille
 * @details Crée un widget une grille et l'initialise avec les propriétés voulus
 * dans notre application.
 * @return GtkWidget Pointeur sur le widget.
 * @author Pierre Ayoub et Damien Delaunay
 */
GtkWidget *ui_grid_init();

/**
 * @brief Crée un dialogue.
 * @details Crée un dialogue selon une configuration pré-définie de
 * l'application.
 * @param win Fenêtre parente du dialogue.
 * @param str Chaîne de caractère à afficher.
 * @param ui_type Nature du dialogue.
 * @return GtkWidget* Widget de type "GtkMessageDialog" prêt à être affiché.
 * @author Pierre Ayoub et Damien Delaunay
 */
GtkWidget *ui_msg_dial_new(GtkWidget * win, const gchar * str, enum ui_dial_type ui_type);

#endif                          /* UI_MISC_H_ */
