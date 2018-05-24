/**
 * @file detect_algo.h
 * @brief Module de détection de l'algorithme.
 * @details Lecture de la signature d'un fichier hôte.
 */

#ifndef DETECT_ALGO_H
#define DETECT_ALGO_H

/**
 * @brief Saute la signature.
 * @param f Pointeur sur le fichier ou faire le saut.
 * @param h Pointeur sur la chaîne de caractère du nom du fichier dans la
 * signature.
 * @param m Méthode de protection des données utilisé.
 * @return Valeur de "fseek".
 * @author Pierre Ayoub et Damien Delaunay
 */
int sig_fseek(FILE * f, char *h, method_e m);

#endif                          /* ifndef DETECT_ALGO_H */
