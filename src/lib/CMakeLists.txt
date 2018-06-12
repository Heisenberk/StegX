# This file is part of the StegX project.
# Copyright (C) 2018  StegX Team
# 
# StegX is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Auteur : Pierre AYOUB
# ==============================================================================

# Configuration ================================================================

# Windows et MSVC.
if (WIN32 AND MSVC)
    # Exporte automatiquement les symboles du .DLL dans une bibliothèque
    # d'importation .LIB.
    set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
endif ()

# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})
file (GLOB_RECURSE INC_PUBLIC ${SRC_LIB_INC_PATH}/*${INC_EXT})

# Dossiers contenant un header.
# HEADER_DIRECTORIES (INC_DIRS)
set (INC_DIRS src;inc)

# Binaires =====================================================================

# Nom de la cible.
set (TARGET ${SRC_LIB_TARGET})
# Source et dépendances de la bibliothèque.
add_library (${TARGET} SHARED ${SRC} ${INC})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${TARGET} PRIVATE ${INC_DIRS})

# Copie la DLL de la bibliothèque dans le dossier contenant les tests
# pour le linkage lors de l'exécution.
if (WIN32 AND NOT MINGW AND NOT MSYS)
    add_custom_command (TARGET ${SRC_LIB_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${SRC_LIB_TARGET}> ${TEST_OUTPUT_PATH}/$<IF:$<CONFIG:Debug>,Debug,Release>/${SRC_LIB_NAME}.dll
        )
endif ()

# Installation =================================================================

# Propriétés :
# Nom de la bibliothèque.
set_target_properties (${TARGET} PROPERTIES OUTPUT_NAME ${SRC_LIB_NAME})
# Versionnement.
set_target_properties (${TARGET} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (${TARGET} PROPERTIES SOVERSION 1)
# Headers publiques.
set_property (TARGET ${TARGET} PROPERTY PUBLIC_HEADER ${INC_PUBLIC})

# Spécifie les dossiers d'installation de la bibliothèque et de ses headers en
# fonction de l'OS.
if (WIN32)
    set (CMAKE_INSTALL_INCLUDEDIR_CUSTOM ${CMAKE_INSTALL_INCLUDEDIR})
    set (CMAKE_INSTALL_LIBDIR_CUSTOM ${CMAKE_INSTALL_BINDIR})
else ()
    set (CMAKE_INSTALL_INCLUDEDIR_CUSTOM ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME_LC})
    set (CMAKE_INSTALL_LIBDIR_CUSTOM ${CMAKE_INSTALL_LIBDIR})
endif()

# Déclaration de l'installation.
install (TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_LIBDIR_CUSTOM}
    COMPONENT ${SRC_LIB_COMP}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR_CUSTOM}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR_CUSTOM}
    )
