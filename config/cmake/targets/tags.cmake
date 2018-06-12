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

# Génération des tags des sources du projet sur Unix.

# Initialisation.
if (UNIX AND NOT DEFINED TAG_GENERATOR)
    find_program (TAG_GENERATOR ctags)
    if (${TAG_GENERATOR} STREQUAL "TAG_GENERATOR-NOTFOUND")
        message ("-- Could NOT find Ctags (missing: CTAGS_EXECUTABLE)")
        message ("-- Tags will NOT be generated")
        set (TAG_GEN false)
    else ()
        message ("-- Found Ctags: ${TAG_GENERATOR}")
        set (TAG_GEN true)
    endif()
endif()

# Si Ctags est trouvé, il faut repasser ici à chaque configuration de CMake pour
# redéfinir les variables.
if (UNIX AND NOT ${TAG_GENERATOR} STREQUAL "TAG_GENERATOR-NOTFOUND")
    set (TAG_GEN true)
    add_custom_target (
        tags
        DEPENDS tags-${SRC_CLI_DIR} tags-${SRC_GUI_DIR} tags-${SRC_LIB_DIR}
        )
    foreach (type ${SRC_ALL_DIR})
        file (GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/${type}/*${SRC_EXT})
        file (GLOB_RECURSE INC ${CMAKE_CURRENT_SOURCE_DIR}/${type}/*${INC_EXT})
        add_custom_command (OUTPUT tags-${type}
            COMMAND ${TAG_GENERATOR} ${SRC} ${INC}
            COMMAND chown $ENV{USER}:$ENV{USER} tags
            COMMAND ${CMAKE_COMMAND} -E copy tags ${CMAKE_CURRENT_SOURCE_DIR}/${type}/tags
            COMMAND ${CMAKE_COMMAND} -E touch tags-${type}
            DEPENDS ${SRC} ${INC}
            )
    endforeach ()

    # Nettoyage.
    set_property (DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        tags
        )
endif ()
