/**
 * @file ui.h
 * @brief Affichage de l'interface utilisateur
 * @details Affichage de l'interface utilisateur gérant tout ce qui concerne
 * directement ce qui est affiché sur la fenêtre principale. Ne gère que
 * l'affichage et ne concerne pas les signaux, les interfactions et les
 * entrées/sorties.
 */

#ifndef UI_H_
#define UI_H_

/**
 * @brief Construit la fenêtre principale
 * @details Construit la fenêtre principale en ajoutant les conteneurs et les
 * widgets. Ne connecte aucun signaux.
 * @param window Pointeur vers la fenêtre sur laquelle il faut construire
 * l'affichage.
 */
void ui_populate();

#endif /* UI_H_ */
