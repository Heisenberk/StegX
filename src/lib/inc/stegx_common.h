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

enum mode {STEGX_MODE_INSERT, STEGX_MODE_EXTRACT};
typedef enum mode mode_e;

enum algo {STEGX_ALGO_LSB, STEGX_ALGO_EOF, STEGX_ALGO_METADATA, 
	STEGX_ALGO_EOC, STEGX_ALGO_JUNK_CHUNK};
typedef enum algo algo_e;

enum method {STEGX_WITHOUT_PASSWD, STEGX_WITH_PASSWD};
typedef enum method method_e;

typedef struct info info_s;

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
    char* hidden_path;  /*!< chaine de caracteres representant le nom du fichier a cacher (requis). */
    algo_e algo;        /*!< algorithme qui sera utilise pour dissimuler (requis si CLI). */ 
};
typedef struct stegx_info_insert stegx_info_insert_s;

/**
 * @brief Données choisies par l'utilisateur. 
 * @details Représente les données choisies par l'utilisateur s'il veut 
 * dissimuler ou extraire des données.
 */
struct stegx_choices {
    char* host_path;                  /*!< chaine de caracteres representant le chemin du fichier à analyser (requis). */ 
    char* res_path;                   /*!< chaine de caracteres representant le chemin du fichier résultant (requis). */
    char* passwd;                     /*!< chaine de caracteres representant le mot de passe choisi par l'utilisateur (optionnel). */
    mode_e mode;                      /*!< variable représentant ce que l'utilisateur veut faire, soit une extraction soit une dissimulation (requis). */
    stegx_info_insert_s* insert_info; /*!< pointeur sur la structure stockant les informations sur le fichier à cacher (requis si insertion). */ 
};
typedef struct stegx_choices stegx_choices_s;

#endif /* ifndef STEGX_COMMON_H */
