# Projet =======================================================================

# Version de CMake.
cmake_minimum_required (VERSION 3.3)

# Nom du projet et description.
project (StegX VERSION 0.1
    DESCRIPTION "Projet de Stéganographie pour l'UVSQ" 
    LANGUAGES C
    )
set (PROJECT_NAME_LC stegx)

# Mode de compilation.
set (CMAKE_BUILD_TYPE Debug)

# Structure ====================================================================

# Sources.
set (SRC_PATH src)

# Documentation.
set (DOC_PATH doc)

# Rapport.
set (REPORT_PATH report)

# Test unitaires.
enable_testing ()
set (TEST_PATH test)

# Bibliothèques statiques additionnelles.
set (LIB_PATH lib)

# Configuration.
set (CONFIG_PATH config/cmake)
set (CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/${CONFIG_PATH};
        ${CMAKE_SOURCE_DIR}/${CONFIG_PATH}/uninstall
    )

# Raccourcis (.desktop).
set (DESKTOP_PATH ${CONFIG_PATH}/desktop)

# Installation =================================================================

# Cible de désinstallation.
include (uninstall-target)

# Dossiers standards GNU pour l'installation.
include (GNUInstallDirs)

# Macros =======================================================================

# Sous-répertoires.
include (subdirlist)

# Lecture des sous-répertoires =================================================

add_subdirectory (${SRC_PATH})
add_subdirectory (${DOC_PATH})
add_subdirectory (${REPORT_PATH})
add_subdirectory (${TEST_PATH})
