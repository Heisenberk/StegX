/**
 * @file ui_struct.h
 * @brief Structure de l'interface utilisateur
 */

#ifndef UI_STRUCT_H_
#define UI_STRUCT_H_

/**
 * @brief Onglet dissimulation
 * @details Contient tout les widgets utilisés pour l'onglet dissimulation de
 * données.
 */
struct ui_insert
{
    GtkWidget *tab;               /*!< Grille contenant les widgets de l'onglet. */
    GtkWidget *tab_title;         /*!< Titre de l'onglet. */
    GtkWidget *file_orig_lbl;     /*!< Label du bouton de sélection du fichier hôte. */
    GtkWidget *file_orig_fc;      /*!< Bouton de sélection du fichier hôte. */
    GtkWidget *file_to_hide_lbl;  /*!< Label du bouton de sélection du fichier à cacher. */
    GtkWidget *file_to_hide_fc;   /*!< Bouton de sélection du fichier à cacher. */
    GtkWidget *file_out_dir_lbl;  /*!< Label du bouton de sélection du dossier de sortie. */
    GtkWidget *file_out_dir_fc;   /*!< Bouton de sélection du dossier de sortie. */
    GtkWidget *file_out_name_lbl; /*!< Label de l'entrée de texte du nom du fichier de sortie. */
    GtkWidget *file_out_name_ent; /*!< Entrée de texte du nom du fichier de sortie. */
    GtkWidget *algos_lbl;         /*!< Label du bouton de sélection des algorithmes. */
    GtkWidget *algos_cb;          /*!< Bouton de sélection des algorithmes. */
    GtkWidget *passwd_lbl;        /*!< Label de l'entrée de texte du mot de passe. */
    GtkWidget *passwd_ent;        /*!< Entrée de texte du mot de passe. */
    GtkWidget *but;               /*!< bouton de lancement de la dissimulation. */
    gchar *but_lbl_orig;          /*!< Label original du bouton de lancement de la dissimulation. */
    gchar *but_lbl_proc;          /*!< Label pendant le traitement de la dissimulation. */
};

/**
 * @brief Onglet extraction
 * @details Contient tout les widgets utilisés pour l'onglet extraction de
 * données.
 */
struct ui_extrac
{
    GtkWidget *tab;               /*!< Grille contenant les widgets de l'onglet. */
    GtkWidget *tab_title;         /*!< Titre de l'onglet. */
    GtkWidget *file_orig_lbl;     /*!< Label du bouton de sélection du fichier hôte. */
    GtkWidget *file_orig_fc;      /*!< Bouton de sélection du fichier hôte. */
    GtkWidget *file_out_dir_lbl;  /*!< Label du bouton de sélection du dossier de sortie. */
    GtkWidget *file_out_dir_fc;   /*!< Bouton de sélection du dossier de sortie. */
    GtkWidget *passwd_lbl;        /*!< Label de l'entrée de texte du mot de passe. */
    GtkWidget *passwd_ent;        /*!< Entrée de texte du mot de passe. */
    GtkWidget *but;               /*!< Bouton de lancement de l'extraction. */
};

/**
 * @brief Onglet information
 * @details Contient tout les widgets utilisés pour l'onglet d'information sur
 * le logiciel.
 */
struct ui_about
{
    GtkWidget *tab;       /*!< Grille contenant les widgets de l'onglet. */
    GtkWidget *tab_title; /*!< Titre de l'onglet. */
    GtkWidget *info_lbl;  /*!< Label contenant les informations. */
};

/**
 * @brief Interface utilisateur
 * @details Contient tout les widgets utilisés dans l'interface
 * utilisateur.
 */
struct ui
{
    GtkWidget *window;       /*!< Fenêtre principale. */
    GtkWidget *tabs;         /*!< Conteneur des onglets. */
    struct ui_insert insert; /*!< Onglet dissimulation. */
    struct ui_extrac extrac; /*!< Onglet extraction. */
    struct ui_about about;   /*!< Onglet d'information. */
};

#endif /* UI_STRUCT_H_ */
