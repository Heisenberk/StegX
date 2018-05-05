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

enum mode { STEGX_MODE_INSERT, STEGX_MODE_EXTRACT };
typedef enum mode mode_e;

enum algo { STEGX_ALGO_LSB, STEGX_ALGO_EOF, STEGX_ALGO_METADATA,
    STEGX_ALGO_EOC, STEGX_ALGO_JUNK_CHUNK
};
typedef enum algo algo_e;

enum method { STEGX_WITHOUT_PASSWD, STEGX_WITH_PASSWD };
typedef enum method method_e;

typedef struct info info_s;

#define NB_ALGOS 5

/**
 * \def Longueur du mot de passe choisi par défaut
 * */
#define LENGTH_DEFAULT_PASSWD  64       // 64 caractères sans compter le '\0'

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
#define BYTE_EOC_WITHOUT_PASSWD 8

/**
 * \def Signature JUNK CHUNK avec mot de passe choisi par l'utilisateur
 * */
#define BYTE_JUNK_CHUNK_WITH_PASSWD 9

/**
 * \def Signature Junk Chunk sans mot de passe choisi par l'utilisateur, choisi 
 * aléatoirement par l'application
 * */
#define BYTE_JUNK_CHUNK_WITHOUT_PASSWD 10

#define LENGTH_HIDDEN_NAME_MAX 255

/*
 * Variables
 * =============================================================================
 */

algo_e *stegx_propos_algos;

/*
 * Structures
 * =============================================================================
 */

/**
 * @brief Informations du fichier caché. 
 * @details Permet de représenter les informations nécessaires sur le fichier 
 * à cacher, c'est a dire son chemin et l'algorithme que l'on utilisera 
 * pour dissimuler ce dernier.
 */
struct stegx_info_insert {
    char *hidden_path;          /*!< chaine de caracteres representant le nom du fichier a cacher (requis). */
    algo_e algo;                /*!< algorithme qui sera utilise pour dissimuler (requis si CLI). */
};
typedef struct stegx_info_insert stegx_info_insert_s;

/**
 * @brief Données choisies par l'utilisateur. 
 * @details Représente les données choisies par l'utilisateur s'il veut 
 * dissimuler ou extraire des données.
 */
struct stegx_choices {
    char *host_path;            /*!< chaine de caracteres representant le chemin du fichier à analyser (requis). */
    char *res_path;             /*!< chaine de caracteres representant le chemin du fichier résultant (requis). */
    char *passwd;               /*!< chaine de caracteres representant le mot de passe choisi par l'utilisateur (optionnel). */
    mode_e mode;                /*!< variable représentant ce que l'utilisateur veut faire, soit une extraction soit une dissimulation (requis). */
    stegx_info_insert_s *insert_info;   /*!< pointeur sur la structure stockant les informations sur le fichier à cacher (requis si insertion). */
};
typedef struct stegx_choices stegx_choices_s;

#endif                          /* ifndef STEGX_COMMON_H */
