/** 
 * @file stegx_errors.h
 * @brief Module de gestion des erreurs.
 * @details Contient les définitions des codes d'erreurs ainsi que la variable
 * globale utilisée pour communiquer.
 */

#ifndef ERRORS_H
#define ERRORS_H

/**
 * Liste des codes d'erreurs de la bibliothèque. Utilisé dans le retour des
 * fonctions et dans la correspondance erreur <=> message. Le code 0 signifie
 * (sauf cas particulier) qu'aucune erreur ne s'est produite.
 */
enum err_code {
    ERR_NONE = 0,               /*!< Aucune erreur. */
    ERR_OTHER                   /*!< Erreur quelconque. */
};

/**
 * Variable mise à la disposition des fonctions de la bibliothèque pour y
 * inscrire leur code d'erreur.
 */
enum err_code stegx_errno;

/**
 * Affiche le message d'erreur sur la sortie d'erreur en fonction du code
 * d'erreur spécifié.
 * @param err Code d'erreur.
 */
void err_print(const enum err_code err);

#endif                          /* ERRORS_H */
