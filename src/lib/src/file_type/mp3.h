/** 
 * @file mp3.h
 * @brief Fichier MP3.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format MP3.
 */

#ifndef MP3_H
#define MP3_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/** Nombre de bit modifiable à souhait dans un header MPEG 1/2 Layer III. */
#define MP3_HDR_NB_BITS_MODIF 3

/**
 * @brief Structure du format MP3.
 */
struct mp3 {
    long int fr_frst_adr; /*!< Adresse du header de la première frame MPEG 1/2 Layer III. */
    long int fr_nb;       /*!< Nombre de frame MPEG 1/2 Layer III. */
    long int eof;         /*!< Adresse de la fin du fichier officiel (sans signature et données cachées). */
};

/** Type du format MP3. */
typedef struct mp3 mp3_s;

/**
 * @brief Test si le header est un header MPEG 1/2 Layer III.
 * @param hdr Header à tester.
 * @return 0 si le header est incorrect, sinon 1 si le header est valide.
 * @author Pierre Ayoub, Damien Delaunay
 */
int mp3_mpeg_hdr_test(uint32_t hdr);

/**
 * @brief Saute la frame MP3 actuelle.
 * @param hdr Header de la frame MP3 à sauter.
 * @param f Fichier MP3.
 * @return Valeur de retour de fseek().
 * @req Le fichier f doit être ouvert en lecture. Lors du déplacement, il est
 * considéré que le header de la frame vient d'être lu, le curseur de lecture
 * est donc à "debut_de_la_frame + sizeof(hdr)".
 * @sideeffect Le curseur de lecture du fichier est modifié pour sauter la
 * frame.
 * @author Pierre Ayoub, Damien Delaunay
 */
int mp3_mpeg_fr_seek(uint32_t hdr, FILE * f);

/**
 * @brief Trouve la première frame MPEG 1/2 Layer III.
 * @param f Fichier où chercher.
 * @return L'adresse du header de la première frame si elle est trouvée
 * (ftell(f)), sinon -1 sur une erreur.
 * @req Le fichier f doit être ouvert en lecture et bien être un fichier MP3.
 * @sideeffect Modifie l'emplacement du curseur de lecture dans le fichier f.
 * @author Pierre Ayoub, Damien Delaunay
 */
long int mp3_mpeg_fr_find_first(FILE * f);

/**
 * @brief Test si le header est un header ID3v1.
 * @param hdr Header à tester.
 * @return 0 si le header est incorrect, sinon 1 si le header est valide.
 * @author Pierre Ayoub, Damien Delaunay
 */
int mp3_id3v1_hdr_test(uint32_t hdr);

/**
 * @brief Saute le tag ID3v1 actuel.
 * @param f Fichier MP3.
 * @return Valeur de retour de fseek().
 * @req Le fichier f doit être ouvert en lecture. Lors du déplacement, il est
 * considéré que la signature du tag vient d'être lu, le curseur de lecture
 * est donc à "debut_du_tag + sizeof(sig)".
 * @sideeffect Le curseur de lecture du fichier est modifié pour sauter le
 * tag.
 * @author Pierre Ayoub, Damien Delaunay
 */
int mp3_id3v1_tag_seek(FILE * f);

/**
 * @brief Test si le fichier est un fichier MP3.
 * @param file Fichier à tester.
 * @req Le fichier doit être ouvert en lecture.
 * @return \r{MP3}, \r{UNKNOWN} ou -1 en cas d'erreur. 
 * @author Pierre Ayoub, Damien Delaunay
 */
type_e stegx_test_file_mp3(FILE * file);

#endif
