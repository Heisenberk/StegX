# Vérifications ================================================================

# Version de CMake.
cmake_minimum_required (VERSION 3.6 FATAL_ERROR)

# Empêche de lancer une compilation in-source.
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message (FATAL_ERROR "In-source builds not allowed. Please make a new \
    directory (called a build directory) and run CMake from there (cmake ..).")
endif()

# Projet =======================================================================

# Nom du projet et description.
project (StegX VERSION 0.1
    DESCRIPTION "Projet de Stéganographie pour l'UVSQ" 
    LANGUAGES C
    )
string (TOLOWER ${PROJECT_NAME} PROJECT_NAME_LC)
string (TOUPPER ${PROJECT_NAME} PROJECT_NAME_UC)

# Texte de la license sous forme de chaîne de caractère en une ligne pour le C.
file (STRINGS ${CMAKE_SOURCE_DIR}/COPYING PROJECT_LICENSE_FULL_TEXT)
string (REPLACE "\\;" "TRUE_COMMA" PROJECT_LICENSE_FULL_TEXT "${PROJECT_LICENSE_FULL_TEXT}")
string (REPLACE ";" "\\n" PROJECT_LICENSE_FULL_TEXT "${PROJECT_LICENSE_FULL_TEXT}")
string (REPLACE "TRUE_COMMA" ";" PROJECT_LICENSE_FULL_TEXT "${PROJECT_LICENSE_FULL_TEXT}")
string (REPLACE "\"" "\\\"" PROJECT_LICENSE_FULL_TEXT "${PROJECT_LICENSE_FULL_TEXT}")

# Modes de compilation.
set (CMAKE_CONFIGURATION_TYPES Debug;Release)
set (CMAKE_BUILD_TYPE Debug)

# Configuration ================================================================

# Configuration de CMake.
set (CONFIG_DIR config)
set (CONFIG_PATH ${CMAKE_SOURCE_DIR}/${CONFIG_DIR})
set (CMAKE_CONFIG_DIR cmake)
set (CMAKE_CONFIG_PATH ${CONFIG_PATH}/${CMAKE_CONFIG_DIR})

# Dossiers de recherche des modules de CMake.
set (CMAKE_MACRO_DIR macros)
set (CMAKE_MACRO_PATH ${CMAKE_CONFIG_PATH}/${CMAKE_MACRO_DIR})
set (CMAKE_TARGET_DIR targets)
set (CMAKE_TARGET_PATH ${CMAKE_CONFIG_PATH}/${CMAKE_TARGET_DIR})
set (CMAKE_TARGET_UNINSTALL_DIR uninstall)
set (CMAKE_TARGET_UNINSTALL_PATH ${CMAKE_TARGET_PATH}/${CMAKE_TARGET_UNINSTALL_DIR})
set (CMAKE_MODULE_PATH ${CMAKE_MACRO_PATH};${CMAKE_TARGET_PATH};
    ${CMAKE_TARGET_UNINSTALL_PATH})

# Configuration du raccourci (.desktop).
set (DESKTOP_DIR desktop)
set (DESKTOP_PATH ${CONFIG_PATH}/${DESKTOP_DIR})

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

# Répertoire des fichiers sources des tests unitaires.
set (TEST_DIR test)

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
# Nom de la bibliothèque.
set (SRC_LIB_NAME ${PROJECT_NAME_LC})

# Variables communes.
set (SRC_ALL_DIR ${SRC_LIB_DIR} ${SRC_CLI_DIR} ${SRC_GUI_DIR})
set (SRC_ALL_TARGETS ${SRC_LIB_TARGET} ${SRC_CLI_TARGET} ${SRC_GUI_TARGET})
# Dossiers de sortie sur Windows.
if (WIN32)
    set (SRC_RUNTIME_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${SRC_DIR})
    set (TEST_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${TEST_DIR})
endif()

# Lecture des sources.
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
if (NOT MINGW AND NOT MSYS)
    enable_testing ()
    add_subdirectory (${TEST_DIR})
endif ()

# Divers =======================================================================

# Cible de réinitialisation de l'arborescence de build (à faire par exemple si
# on rajoute un fichier source).
add_custom_target (reinit
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} ${CMAKE_BINARY_DIR}
    )

# Formatage des fichiers sources.
include (indent)
