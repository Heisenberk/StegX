/**
 * @file ui.h
 * @brief Gestion de l'interface utilisateur
 * @details Gère l'interface utilisateur. Appel les différentes fonctions
 * permettants de construire l'interface utilisateur et contient les structures
 * de l'interface.
 */

#ifndef UI_H_
#define UI_H_

/**
 * @brief Création de l'interface utilisateur
 * @details Permet de créer entièrement l'interface utilisateur sur une fenêtre
 * donnée. Construit les widgets et configure les signaux.
 * @param window Fenêtre sur laquelle construire l'interface utilisateur.
 */
void ui_create(GtkWidget *window);

#endif /* UI_H_ */
