/**
 * @file struct.h
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
    /* Statique. */
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
    /* Dynamique. */
    GtkWidget *but;               /*!< Bouton de lancement du traitement de l'étape en cours. */
    GtkWidget *but_reset;         /*!< Bouton de réinitialisation. */
    GtkWidget *dial;              /*!< Dialogue en cours d'affichage. */
    gchar *dial_anal_cond;        /*!< Message du dialogue d'information d'analyse si les conditions initiales ne sont pas remplies. */
    gchar *dial_anal_proc;        /*!< Message du dialogue d'information d'analyse pendant le traitement. */
    gchar *dial_anal_end;         /*!< Message du dialogue d'information d'analyse terminé. */
    gchar *dial_anal_err;         /*!< Message du dialogue d'information d'analyse interrompu par une erreur. */
    gchar *dial_dissi_cond;       /*!< Message du dialogue d'information de dissimulation si les conditions initiales ne sont pas remplies. */
    gchar *dial_dissi_proc;       /*!< Message du dialogue d'information de dissimulation pendant le traitement. */
    gchar *dial_dissi_end;        /*!< Message du dialogue d'information de dissimulation terminé. */
    gchar *dial_dissi_err;        /*!< Message du dialogue d'information de dissimulation interrompu par une erreur. */
    gchar *but_txt_anal;          /*!< Texte du bouton de lancement de l'analyse. */
    gchar *but_txt_anal_proc;     /*!< Texte du bouton de lancement de l'analyse pendant le traitement. */
    gchar *but_txt_dissi;         /*!< Texte du bouton de lancement de la dissimilation. */
    gchar *but_txt_dissi_proc;    /*!< Texte du bouton de lancement de la dissimilation pendant le traitement. */
    gchar *but_txt_reset;         /*!< Texte du bouton de réinitialisation. */
};

/**
 * @brief Onglet extraction
 * @details Contient tout les widgets utilisés pour l'onglet extraction de
 * données.
 */
struct ui_extrac
{
    GtkWidget *tab;              /*!< Grille contenant les widgets de l'onglet. */
    GtkWidget *tab_title;        /*!< Titre de l'onglet. */
    GtkWidget *file_orig_lbl;    /*!< Label du bouton de sélection du fichier hôte. */
    GtkWidget *file_orig_fc;     /*!< Bouton de sélection du fichier hôte. */
    GtkWidget *file_out_dir_lbl; /*!< Label du bouton de sélection du dossier de sortie. */
    GtkWidget *file_out_dir_fc;  /*!< Bouton de sélection du dossier de sortie. */
    GtkWidget *passwd_lbl;       /*!< Label de l'entrée de texte du mot de passe. */
    GtkWidget *passwd_ent;       /*!< Entrée de texte du mot de passe. */
    GtkWidget *but;              /*!< Bouton de lancement de l'extraction. */
    GtkWidget *dial;             /*!< Dialogue en cours d'affichage. */
    gchar *dial_cond;            /*!< Message du dialogue d'information de l'extraction si les conditions initiales ne sont pas remplies. */
    gchar *dial_proc;            /*!< Message du dialogue d'information de l'extraction pendant le traitement. */
    gchar *dial_end;             /*!< Message du dialogue d'information de l'extraction terminé. */
    gchar *dial_err;             /*!< Message du dialogue d'information de l'extraction interrompu par une erreur. */
    gchar *but_txt;              /*!< Texte du bouton de lancement de l'extraction. */
    gchar *but_txt_proc;         /*!< Texte du bouton de lancement de l'extraction pendant le traitement. */
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
 * @brief Menu
 * @details Menu principal de l'application. Contient les widgets utilisés dans
 * le menu ainsi que le widget du menu lui-même.
 */
struct ui_menu
{
    GtkWidget *bar;   /*!< Barre du menu. */
    GtkWidget *about; /*!< Bouton à propos. */
};

/**
 * @brief Interface utilisateur
 * @details Contient tout les widgets utilisés dans l'interface
 * utilisateur.
 */
struct ui
{
    GtkWidget *window;       /*!< Fenêtre principale. */
    GtkWidget *box;          /*!< Conteneur principal. */
    GtkWidget *tabs;         /*!< Conteneur des onglets. */
    struct ui_insert insert; /*!< Onglet dissimulation. */
    struct ui_extrac extrac; /*!< Onglet extraction. */
    struct ui_about about;   /*!< Onglet d'information. */
    struct ui_menu menu;     /*!< Menu de l'application. */
};

#endif /* UI_STRUCT_H_ */
