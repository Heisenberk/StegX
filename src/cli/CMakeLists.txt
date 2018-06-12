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

# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})

# Dossiers contenant un header.
# HEADER_DIRECTORIES(INC_DIRS)
set (INC_DIRS ./)

# Binaire ======================================================================

# Nom de la cible.
set (TARGET ${SRC_CLI_TARGET})
# Sources et dépendances de l'exécutable.
add_executable (${TARGET} ${SRC} ${INC})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${TARGET} PRIVATE ${INC_DIRS} ${SRC_LIB_INC_PATH})

# Bibliothèque à passer au linker.
target_link_libraries (${TARGET} ${SRC_LIB_TARGET})

# Installation =================================================================

# Nom de l'exécutable.
set_target_properties (${TARGET} PROPERTIES OUTPUT_NAME ${PROJECT_NAME_LC})

# Déclaration de l'installation.
install (TARGETS ${TARGET}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT ${SRC_CLI_COMP}
	)
