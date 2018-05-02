/**
 * @file misc.c
 * @brief Fonctions diverses pour GTK+
 * @details Contient des fonctions diverses utilisant les fonctions de GTK+ afin
 * de factoriser du code et d'avoir des raccourcis.
 */

#include <gtk/gtk.h>
#include "misc.h"

GtkWidget *ui_grid_init()
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

GtkWidget *ui_msg_dial_new(GtkWidget * win, const gchar * str, enum ui_dial_type ui_type)
{
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkMessageType type;
    GtkButtonsType buttons;
    if (ui_type == UI_DIAL_INFO_WAIT || ui_type == UI_DIAL_INFO_OK) {
        type = GTK_MESSAGE_INFO;
        buttons = (ui_type == UI_DIAL_INFO_WAIT) ? GTK_BUTTONS_NONE : GTK_BUTTONS_OK;
    } else if (ui_type == UI_DIAL_WARN || ui_type == UI_DIAL_ERR) {
        buttons = GTK_BUTTONS_CANCEL;
        type = (ui_type == UI_DIAL_WARN) ? GTK_MESSAGE_WARNING : GTK_MESSAGE_ERROR;
    }
    return gtk_message_dialog_new(GTK_WINDOW(win), flags, type, buttons, str, NULL);
}
