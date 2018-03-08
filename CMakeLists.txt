# Projet =======================================================================

# Version de CMake.
cmake_minimum_required (VERSION 3.3)

# Nom du projet et description.
project (StegX VERSION 0.1
    DESCRIPTION "Projet de Stéganographie pour l'UVSQ" 
    LANGUAGES C
    )
string (TOLOWER ${PROJECT_NAME} PROJECT_NAME_LC)
string (TOUPPER ${PROJECT_NAME} PROJECT_NAME_UC)

# Mode de compilation.
set (CMAKE_BUILD_TYPE Debug)

# Configuration ================================================================

# Configuration de CMake.
set (CONFIG_DIR config)
set (CMAKE_CONFIG_DIR cmake)
set (CMAKE_CONFIG_PATH ${CMAKE_SOURCE_DIR}/${CONFIG_DIR}/${CMAKE_CONFIG_DIR})

# Dossiers de recherche des modules de CMake.
set (CMAKE_MODULE_PATH ${CMAKE_CONFIG_PATH};
    ${CMAKE_CONFIG_PATH}/uninstall;
    ${CMAKE_CONFIG_PATH}/macros)

# Configuration du raccourci (.desktop).
set (DESKTOP_DIR desktop)
set (DESKTOP_PATH ${CMAKE_CONFIG_PATH}/${DESKTOP_DIR})

# Macros =======================================================================

# Créer une liste des sous-répertoires.
include (subdirlist)
# Créer une liste de répertoires contenant des headers.
include (headers-directories)

# Sources ======================================================================

# Répertoires des sources du projet et des bibliothèques utilisées.
set (SRC_DIR src)
set (LIB_DIR lib)

# Extension des fichiers sources et des headers.
set (SRC_EXT .c)
set (INC_EXT .h)

# Répertoires des différentes cibles :
# Bibliothèque StegX.
set (SRC_LIB_DIR lib)
# Interface en ligne de commande.
set (SRC_CLI_DIR cli)
# Interface graphique.
set (SRC_GUI_DIR gui)

# Noms des différentes cibles :
# Bibliothèque StegX.
set (SRC_LIB_TARGET ${PROJECT_NAME_LC}-${SRC_LIB_DIR})
# Interface en ligne de commande.
set (SRC_CLI_TARGET ${PROJECT_NAME_LC}-${SRC_CLI_DIR})
# Interface graphique.
set (SRC_GUI_TARGET ${PROJECT_NAME_LC}-${SRC_GUI_DIR})

# Bibliothèque StegX :
# Headers publiques.
set (SRC_LIB_INC_DIR inc)
set (SRC_LIB_INC_PATH
    ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${SRC_LIB_DIR}/${SRC_LIB_INC_DIR})
# Headers privés.
set (SRC_LIB_SRC_DIR src)
set (SRC_LIB_SRC_PATH
    ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${SRC_LIB_DIR}/${SRC_LIB_SRC_DIR})

# Variables communes.
set (SRC_ALL_DIR ${SRC_LIB_DIR} ${SRC_CLI_DIR} ${SRC_GUI_DIR})
set (SRC_ALL_TARGETS ${SRC_LIB_TARGET} ${SRC_CLI_TARGET} ${SRC_GUI_TARGET})
# Lecture.
add_subdirectory (${SRC_DIR})

# Documentation ================================================================

# Lecture du répertoire de la configuration de la documentation.
set (DOC_DIR doc)
add_subdirectory (${DOC_DIR})

# Rapports =====================================================================

# Lecture du répertoire de la configuration des rapports.
set (REPORT_DIR report)
add_subdirectory (${REPORT_DIR})

# Tests unitaires ==============================================================

# Activation des tests unitaires, puis lecture du répertoire contenant la
# configuration des tests.
enable_testing ()
set (TEST_DIR test)
add_subdirectory (${TEST_DIR})
