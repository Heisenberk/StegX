/**
 * @file ui.h
 * @brief Gestion de l'interface utilisateur
 * @details Gère l'interface utilisateur. Appel les différentes fonctions
 * permettants de construire l'interface utilisateur et de gérer les
 * interactions.
 */

#ifndef UI_H_
#define UI_H_

/** Type de l'interface utilisateur. */
typedef struct ui ui_t;

/**
 * @brief Création de l'interface utilisateur
 * @details Permet de créer entièrement l'interface utilisateur sur une fenêtre
 * donnée. Construit les widgets et configure les signaux.
 * @param window Pointeur vers la fenêtre sur laquelle construire l'interface utilisateur.
 * @param ui Pointeur vers l'interface utilisateur à remplir.
 */
void ui_create(GtkWidget * window, struct ui *ui);

/**
 * @brief Initialisation de l'interface utilisateur
 * @details Permet d'allouer la mémoire pour l'interface utilisateur.
 * @return Pointeur sur l'interface utilisateur prête à être construite.
 */
ui_t *ui_init();

/**
 * @brief Suppression de l'interface utilisateur
 * @details Permet de désallouer la mémoire utilisée pour l'interface
 * utilisateur.
 */
void ui_delete(ui_t * ui);

#endif                          /* UI_H_ */
