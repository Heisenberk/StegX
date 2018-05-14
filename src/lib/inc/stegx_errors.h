/** 
 * @file stegx_errors.h
 * @brief Module de gestion des erreurs.
 * @details Contient les définitions des codes d'erreurs ainsi que la variable
 * globale utilisée pour communiquer.
 */

#ifndef ERRORS_H
#define ERRORS_H

/**
 * @error Liste des codes d'erreurs de la bibliothèque. Utilisé dans le retour des
 * fonctions et dans la correspondance erreur <=> message. Le code 0 signifie
 * (sauf cas particulier) qu'aucune erreur ne s'est produite.
 */
enum err_code {
    ERR_NONE = 0,      /*!< Aucune erreur. */
    ERR_HOST,          /*!< Erreur pendant l'ouverture du fichier hôte. */
    ERR_HIDDEN,        /*!< Erreur pendant l'ouverture du fichier à cacher. */
    ERR_PASSWD,        /*!< Mot de passe invalide. */
    ERR_RES_EXTRACT,   /*!< Resultat doit être un dossier en extract. */
    ERR_RES_INSERT,    /*!< Resultat invalide pour l'insertion. */
    ERR_READ,          /*!< Erreur lors de la lecture. */
    ERR_CHECK_COMPAT,  /*!< Erreur dans le module Verification de la compatibilite des fichiers. */
    ERR_SUGG_ALGOS,    /*!< Erreur dans le sous-module proposition des algos de steganographie. */
    ERR_CHOICE_ALGO,   /*!< Erreur l'algorithme choisi par l'utilisateur n'est proposé. */
    ERR_INSERT,        /*!< Erreur dans le sous-module Insertion. */
    ERR_EXTRACT,       /*!< Erreur dans le sous-module Extraction. */
    ERR_DETECT_ALGOS,  /*!< Erreur dans le sous-module Dectection des algorithmes de steganographie. */
    ERR_LENGTH_HIDDEN, /*!< Erreur taille du fichier à cacher trop élevée */
    ERR_NEED_PASSWD,   /*!< Erreur l'application a besoin d'un mot de passe pour extraire les données. */
    ERR_OTHER          /*!< Erreur quelconque. */
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
