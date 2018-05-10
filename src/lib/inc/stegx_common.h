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
 * fichier hôte).
 */
enum algo {
    STEGX_ALGO_LSB = 0,         /*!< Least Significant Bit : modification du bit de poids faible. */
    STEGX_ALGO_EOF,             /*!< End-Of-File : concaténation avec le fichier à cacher. */
    STEGX_ALGO_METADATA,        /*!< Métadonnée : stockage du fichier à cacher dans les métadonnées du fichier hôte. */
    STEGX_ALGO_EOC,             /*!< End-Of-Chunk : stockage du fichier à cacher après chaque chunk. */
    STEGX_ALGO_JUNK_CHUNK,      /*!< Chunk poubelle : stockage du fichier dans des chunks invalides. */
    STEGX_NB_ALGO               /*!< Nombres d'algorithmes proposés par l'application. */
};

/** Type d'un l'agortihme. */
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
attention les octets 8 (8 en hexa), 9 (9 en hexa), 18 (12 en hexa) et 24 (18 en hexa) 
ne peuvent pas etre utilisés dans le premier octet de la signature StegX 
a cause de la signature FLV des différents tags.
*/

/**
 * \def Signature EOF avec mot de passe choisi par l'utilisateur
 * */
#define BYTE_EOF_WITH_PASSWD 1

/**
 * \def Signature EOF sans mot de passe choisi par l'utilisateur, choisi 
 * aléatoirement par l'application
 * */
#define BYTE_EOF_WITHOUT_PASSWD 2

/**
 * \def Signature LSB avec mot de passe choisi par l'utilisateur
 * */
#define BYTE_LSB_WITH_PASSWD 3

/**
 * \def Signature LSB sans mot de passe choisi par l'utilisateur, choisi 
 * aléatoirement par l'application
 * */
#define BYTE_LSB_WITHOUT_PASSWD 4

/**
 * \def Signature METADATA avec mot de passe choisi par l'utilisateur
 * */
#define BYTE_METADATA_WITH_PASSWD 5

/**
 * \def Signature METADATA sans mot de passe choisi par l'utilisateur, choisi 
 * aléatoirement par l'application
 * */
#define BYTE_METADATA_WITHOUT_PASSWD 6

/**
 * \def Signature EOC avec mot de passe choisi par l'utilisateur
 * */
#define BYTE_EOC_WITH_PASSWD 7

/**
 * \def Signature EOC sans mot de passe choisi par l'utilisateur, choisi 
 * aléatoirement par l'application
 * */
#define BYTE_EOC_WITHOUT_PASSWD 10

/**
 * \def Signature JUNK CHUNK avec mot de passe choisi par l'utilisateur
 * */
#define BYTE_JUNK_CHUNK_WITH_PASSWD 11

/**
 * \def Signature Junk Chunk sans mot de passe choisi par l'utilisateur, choisi 
 * aléatoirement par l'application
 * */
#define BYTE_JUNK_CHUNK_WITHOUT_PASSWD 13

#define LENGTH_HIDDEN_NAME_MAX 255

/**
 * \def Longueur du mot de passe choisi par défaut
 * */
#define LENGTH_DEFAULT_PASSWD  64       // 64 caractères sans compter le '\0'

/*
 * Variables
 * =============================================================================
 */

/**
 * Variable globale pointant sur un tableau de booléen de taille \r{STEGX_NB_ALGO}.
 * Si stegx_propos_algo[i] est égal à 1, alors on peut utiliser l'aglorithme
 * correspondant à algo_e égal à i. Sinon, on ne peut pas.
 */
algo_e *stegx_propos_algos;

/*
 * Structures
 * =============================================================================
 */

/** Informations concernant uniquement l'insertion de données. */
struct stegx_info_insert {
    char *hidden_path;          /*!< Chaîne de caractères representant le nom du fichier a cacher (requis). */
    algo_e algo;                /*!< Rlgorithme qui sera utilisé pour la dissimulation (requis uniquement si CLI). */
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
    char *host_path;            /*!< Chemin du fichier à analyser (requis). */
    char *res_path;             /*!< Chemin du fichier résultant (requis). */
    char *passwd;               /*!< Mot de passe choisi par l'utilisateur (optionnel). */
    mode_e mode;                /*!< Mode d'utilisation (requis). */
    stegx_info_insert_s *insert_info;   /*!< Structure stockant les informations de l'insertion (requis si insertion). */
};

/** Type des informations du choix de l'utilisateur. */
typedef struct stegx_choices stegx_choices_s;

#endif                          /* ifndef STEGX_COMMON_H */
