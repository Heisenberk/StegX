/**
 * @file stegx_common.h
 * @brief Définitions communes à la partie privée et public de la bibliothèque.
 * @details Ce fichier peut-être inclus par les programme utilisant la
 * bibliothèque ainsi que par les différents modules de la bibliothèque. Il
 * contient des types, des structures et des variables globales.
 */

#ifndef STEGX_COMMON_H
#define STEGX_COMMON_H

/*
 * Types
 * =============================================================================
 */

/**
 * Mode permettant de distinguer les deux fonctionnalités proposés par
 * l'application.
 * */
enum mode {
    STEGX_MODE_INSERT,          /*!< Mode insertion/dissimulation de données. */
    STEGX_MODE_EXTRACT          /*!< Mode extraction de données. */
};

/** Type du mode d'utilisation de la bibliothèque. */
typedef enum mode mode_e;

/**
 * Algorithmes proposés par l'application (sans prendre compte du format du
 * fichier hôte) (attention, l'ordre ne doit pas être modifié).
 */
enum algo {
    STEGX_ALGO_LSB = 0,         /*!< Least Significant Bit : modification du bit de poids faible. */
    STEGX_ALGO_EOF,             /*!< End-Of-File : concaténation avec le fichier à cacher. */
    STEGX_ALGO_METADATA,        /*!< Métadonnée : stockage du fichier à cacher dans les métadonnées du fichier hôte. */
    STEGX_ALGO_EOC,             /*!< End-Of-Chunk : stockage du fichier à cacher après chaque chunk. */
    STEGX_ALGO_JUNK_CHUNK,      /*!< Chunk poubelle : stockage du fichier dans des chunks invalides. */
    STEGX_NB_ALGO               /*!< Nombres d'algorithmes proposés par l'application. */
};

/** Type d'un algortihme proposé par l'application. */
typedef enum algo algo_e;

/** Méthode de protection des données. */
enum method {
    STEGX_WITHOUT_PASSWD,       /*!< Aucun mot de passe choisi par l'utilisateur. */
    STEGX_WITH_PASSWD           /*!< Mot de passe choisi par l'utilisateur. */
};

/** Type de la méthode de protection des données. */
typedef enum method method_e;

/** Type de la structure privée stockant les informations de la bibliothèque. */
typedef struct info info_s;

/*
 * Variables
 * =============================================================================
 */

/**
 * Variable globale pointant sur un tableau de booléen de taille \r{STEGX_NB_ALGO}.
 * Si stegx_propos_algo[i] est égal à 1, alors on peut utiliser l'algorithme
 * correspondant à algo_e égal à i. Sinon, on ne peut pas.
 */
extern algo_e *stegx_propos_algos;

/*
 * Structures
 * =============================================================================
 */

/**
 * @brief Informations concernant uniquement l'insertion de données. 
 */
struct stegx_info_insert {
    char *hidden_path;          /*!< Chaîne de caractères representant le nom du fichier a cacher (requis). */
    algo_e algo;                /*!< Algorithme qui sera utilisé pour la dissimulation (requis uniquement si CLI). */
};

/** Type des informations concernant uniquement l'insertion. */
typedef struct stegx_info_insert stegx_info_insert_s;

/**
 * @brief Informations du choix de l'utilisateur. 
 * @details Cette structure est à remplir par les interfaces avec les choix de
 * l'utilisateur.
 * @req Les pointeurs ne doivent pas êtres null pour les champs requis et
 * doivent pointer sur des zones mémoires allouées.
 */
struct stegx_choices {
    char *host_path;            /*!< Chemin du fichier hôte à analyser (requis). */
    char *res_path;             /*!< Chemin du fichier/dossier résultant (requis). */
    char *passwd;               /*!< Mot de passe choisi par l'utilisateur (optionnel). */
    mode_e mode;                /*!< Mode d'utilisation (requis). */
    stegx_info_insert_s *insert_info;   /*!< Structure stockant les informations de l'insertion (requis si insertion). */
};

/** Type des informations du choix de l'utilisateur. */
typedef struct stegx_choices stegx_choices_s;

#endif                          /* ifndef STEGX_COMMON_H */
