# Projet =======================================================================

# Version de CMake.
cmake_minimum_required (VERSION 3.3)

# Nom du projet et description.
project (StegX VERSION 0.1 DESCRIPTION "Projet de Stéganographie pour l'UVSQ")

# Mode de compilation.
set (CMAKE_BUILD_TYPE Debug)

# Paramètres ===================================================================

# Dosser d'installation
# if (UNIX AND ${CMAKE_INSTALL_PREFIX} STREQUAL "/usr/local")
    # set (CMAKE_INSTALL_PREFIX /opt)
# endif()

# Structure ====================================================================

# Sources
set (SRC_PATH src)
add_subdirectory (${SRC_PATH})

# Documentation
# set (DOC_PATH doc)
# add_subdirectory (${DOC_PATH})

# Rapport
# set (REPORT_PATH report)
# add_subdirectory (${REPORT_PATH})
