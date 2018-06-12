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

# Génération des rapports du projet.

# Initialisation.
if (NOT DEFINED PDFLATEX_COMPILER)
    # Recherche de LaTeX.
    find_package (LATEX COMPONENTS PDFLATEX)
    if (NOT PDFLATEX_COMPILER)
        message ("-- Report will NOT be generated")
    endif()
endif ()

# Si LaTeX est trouvé.
if (PDFLATEX_COMPILER)
    # Si compilation en mode Release, alors le rapport sera généré
    # automatiquement lorsque l'on fait make et les détailes ne seront pas
    # affichés.
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set (MODE ALL)
        if (WIN32)
            set (OUTPUT_OPTIONS > nul)
        elseif (UNIX)
            set (OUTPUT_OPTIONS > /dev/null)
        endif ()
    endif ()

    # Variables
    set (REPORT_TARGET_NAME report)
    SUBDIRLIST (LATEX_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

    # Commandes de génération de chaque rapport.
    foreach (subdir ${LATEX_DIRS})
        set (LATEX_CURR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        file (GLOB_RECURSE LATEX_INPUTS ${LATEX_CURR_DIR}/*.tex)
        foreach (latex_input ${LATEX_INPUTS})
            set (LATEX_OUTPUT_DIR
                ${CMAKE_CURRENT_BINARY_DIR}/${subdir})
            set (LATEX_OUTPUT_PATH
                ${CMAKE_CURRENT_BINARY_DIR}/${subdir}/${LATEX_INPUT_NAME})
            get_filename_component (LATEX_OUTPUT_NAME ${latex_input} NAME_WE)
            set (LATEX_OUTPUT_NAME ${LATEX_OUTPUT_NAME}.pdf)
            add_custom_command (OUTPUT ${subdir}/${LATEX_OUTPUT_NAME}
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                        ${LATEX_OUTPUT_DIR}
                    COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_CURR_DIR}
                        ${PDFLATEX_COMPILER} -output-directory
                        ${LATEX_OUTPUT_DIR} ${latex_input} ${OUTPUT_OPTIONS}
                    DEPENDS ${latex_input}
                )
            list (APPEND REPORT_TARGET_DEPENDS ${subdir}/${LATEX_OUTPUT_NAME})
        endforeach ()
    endforeach ()

    # Cible de génération des rapports.
    add_custom_target (${REPORT_TARGET_NAME} ${MODE}
        DEPENDS ${REPORT_TARGET_DEPENDS})

    # Nettoyage.
    set_property (DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        ${LATEX_DIRS}
        )
endif ()
