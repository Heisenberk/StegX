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

# Formatage des sources du projet sur Unix.

# Initialisation.
if (UNIX AND NOT DEFINED INDENT_COMMAND)
    find_program (INDENT_COMMAND indent)
    if (${INDENT_COMMAND} STREQUAL "INDENT_COMMAND-NOTFOUND")
        message ("-- Could NOT find GNU Indent (missing: INDENT_EXECUTABLE)")
        message ("-- Source code will NOT be formated")
    else ()
        message ("-- Found GNU Indent: ${INDENT_COMMAND}")
    endif()
endif()

# Si Indent est trouvé, il faut repasser ici à chaque configuration de CMake
# pour redéfinir les variables.
if (UNIX AND NOT ${INDENT_COMMAND} STREQUAL "INDENT_COMMAND-NOTFOUND")
    add_custom_target (
        indent
        DEPENDS indent-${SRC_CLI_DIR} indent-${SRC_GUI_DIR} indent-${SRC_LIB_DIR}
        )
    foreach (type ${SRC_ALL_DIR})
        file (GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${type}/*${SRC_EXT}
            ${CMAKE_SOURCE_DIR}/${TEST_DIR}/${type}/*${SRC_EXT})
        file (GLOB_RECURSE INC ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${type}/*${INC_EXT}
            ${CMAKE_SOURCE_DIR}/${TEST_DIR}/${type}/*${INC_EXT})
        add_custom_command (OUTPUT indent-${type}
            COMMAND ${CMAKE_COMMAND} -E chdir "${CONFIG_PATH}/indent" ${INDENT_COMMAND} ${SRC} ${INC}
            COMMAND ${CMAKE_COMMAND} -E touch indent-${type}
            DEPENDS ${SRC} ${INC}
            )
        foreach (src_file ${SRC} ${INC})
            list (APPEND FILE_TO_CLEAN ${src_file}~)
        endforeach ()
    endforeach ()

    # Nettoyage.
    set_property (DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        ${FILE_TO_CLEAN}
        )
endif ()
