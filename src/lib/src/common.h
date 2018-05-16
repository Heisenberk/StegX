/**
 * @file common.h
 * @brief Définitions communes à la partie privée de la bibliothèque.
 * @details Ce fichier peut-être inclus par les différents modules de la
 * bibliothèque.
 */

#ifndef COMMON_PRIV_H
#define COMMON_PRIV_H

#include <stdio.h>
#include <stdint.h>

#include "stegx_common.h"

/*
 * Types
 * =============================================================================
 */

/**
 * @brief Test si le paramètre correspond à un format de fichier connu par
 * l'application.
 * @param enum_type Enumération de type à tester.
 * @return 1 si le type est connu, 0 sinon.
 */
#define IS_FILE_TYPE(enum_type)                                           \
        (enum_type > UNKNOWN && enum_type <= FLV ? 1 : 0);

/**
 * @brief Types de fichiers possibles pour le fichier hôte.
 * @internal Attention à ne pas changer l'ordre.
 */
enum type {
    UNKNOWN = 0,                /*!< Type de fichier inconnu. */
    BMP_COMPRESSED,             /*!< Fichier BMP compressé. */
    BMP_UNCOMPRESSED,           /*!< Fichier BMP non-compressé. */
    WAV_PCM,                    /*!< Fichier WAVE-PCM. */
    WAV_NO_PCM,                 /*!< Fichier WAVE contenant un flux non-PCM. */
    PNG,                        /*!< Fichier PNG. */
    MP3,                        /*!< Fichier MP3. */
    AVI_COMPRESSED,             /*!< Fichier AVI compressé. */
    AVI_UNCOMPRESSED,           /*!< Fichier AVI non-compressé. */
    FLV                         /*!< Fichier FLV (doit rester le dernier dans la liste). */
};

/** Type des types de fichiers. */
typedef enum type type_e;

/*
 * Structures
 * =============================================================================
 */

#include "file_type/bmp.h"
#include "file_type/png.h"
#include "file_type/wav.h"
#include "file_type/mp3.h"
#include "file_type/avi.h"
#include "file_type/flv.h"

/** Informations concernant le fichier hôte. */
struct host_info {
    FILE *host;                 /*!< Pointeur vers le fichier hôte. */
    type_e type;                /*!< Type du fichier hôte. */
    union file_info_u {
        struct bmp bmp;
        struct png png;
        struct wav wav;
        struct mp3 mp3;
        struct avi avi;
        struct flv flv;
    } file_info;                /*!< Structure du format du fichier hôte. */
};

/** Type du fichier hôte. */
typedef struct host_info host_info_s;

/**
 * Informations utiles aux fonctions de la bibliothèque pour l'insertion et la
 * dissimulation. 
 */
struct info {
    mode_e mode;                /*!< Mode d'utilisation de la bibliothèque (requis). */
    algo_e algo;                /*!< Algorithme utilisé. */
    method_e method;            /*!< Méthode de protection de données utilisé. */
    host_info_s host;           /*!< Fichier hôte. */
    FILE *res;                  /*!< Fichier résultat qui va être créé pour l'insertion ou l'extraction (requis). */
    FILE *hidden;               /*!< Fichier à cacher (requis lors de l'insertion). */
    char *hidden_name;          /*!< Nom du fichier à cacher / du fichier chaché (requis, calculé à partir de hidden_path). */
    uint32_t hidden_length;     /*!< Taille du fichier à cacher / du fichier caché (octets). */
    char *passwd;               /*!< Mot de passe choisi par l'utilisateur. */
};

/*
 * Signature
 * =============================================================================
 */

/* Attention : les octets 8 (0x8), 9 (0x9), 18 (0x12) et 24 (0x18) ne peuvent pas
 * etre utilisés dans le premier octet de la signature StegX à cause de la
 * signature des différents tags dans FLV. */

/** Taille maximale pour le nom du fichier caché. */
#define LENGTH_HIDDEN_NAME_MAX 255

/** Longueur du mot de passe choisi par défaut. */
#define LENGTH_DEFAULT_PASSWD  64       /* 64 caractères sans compter le '\0'. */

/*
 * Autres
 * =============================================================================
 */

/** Taille du fichier a cacher à partir duquel on utilise un XOR au lieu du 
 *  mélange aléatoire des octets cachés (octets). */
#define LENGTH_HIDDEN_FILE_MAX 150000

#endif                          /* ifndef COMMON_PRIV_H */
