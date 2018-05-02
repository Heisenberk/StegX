/**
 * @file builder.h
 * @brief Construction des wigets et des structures
 * @details Construction de l'interface utilisateur gérant tout ce qui concerne
 * directement ce qui est affiché sur la fenêtre principale. Ne gère pas les
 * signaux, les interfactions et les entrées/sorties.
 */

#ifndef UI_BUILDER_H_
#define UI_BUILDER_H_

#include "struct.h"

/**
 * @brief Construit la fenêtre principale
 * @details Construit la fenêtre principale en ajoutant les conteneurs et les
 * widgets. Ne connecte aucun signal.
 * @param ui Pointeur vers la structure de l'interface utilisateur sur laquelle
 * il faut construire l'affichage.
 */
void ui_build(struct ui *ui);

#endif                          /* UI_BUILDER_H_ */
