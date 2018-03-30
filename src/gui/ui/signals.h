/**
 * @file signals.h
 * @brief Configuration des signaux
 * @details Configure les signaux de l'interface utilisateur. Ne gère que les
 * signaux et les interfactions, ne concerne pas l'affichage statique.
 */

#ifndef UI_SIGNALS_H_
#define UI_SIGNALS_H_

#include "struct.h"

/**
 * @brief Initialise les signaux
 * @details Connecte les signaux aux widgets de la fenêtre principale.
 * @param ui Pointeur vers la structure de l'interface utilisateur sur laquelle
 * il faut configurer les signaux.
 */
void ui_signal_init(struct ui *ui);

#endif /* UI_SIGNALS_H_ */
