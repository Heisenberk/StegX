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

# Liste des fichiers sources tests.
file (GLOB_RECURSE TEST_FILES *${SRC_EXT})

# Déclaration de toutes les cibles correspondant aux tests.
foreach (test_file ${TEST_FILES})
    # Nom du test et ajout dans la liste pour le CMakeLists parent.
    get_filename_component (TEST_NAME ${test_file} NAME_WE)
    list (APPEND TEST_NAMES ${TEST_NAME})
    # Nom du fichier contenant les flags. Si le fichier de flags existe, alors
    # on le lit et on le stock dans une variable.
    set (TEST_FLAG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.${FLAG_EXT})
    if (EXISTS ${TEST_FLAG_FILE})
        file (STRINGS ${TEST_FLAG_FILE} TEST_FLAG)
    endif()

    # Déclaration du fichier source comme cible exécutable et comme test.
    add_executable (${TEST_NAME} EXCLUDE_FROM_ALL ${test_file})
    add_test (NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    # Inclusion et linkage de CMocka.
    target_include_directories (${TEST_NAME} PRIVATE ${CMOCKA_PATH}/${CMOCKA_INC_DIR})
    target_link_libraries (${TEST_NAME} ${CMOCKA_LIBRARY})

    # Ajout des flags personnalisés s'ils ont étés spécifiés.
    if (TEST_FLAG)
        target_compile_options (${TEST_NAME} PRIVATE ${TEST_FLAG})
    endif()

    # Inclusion et linkage de bibliothèque supplémentaire.
    target_include_directories (${TEST_NAME} PRIVATE ${SRC_LIB_SRC_PATH})
    target_include_directories (${TEST_NAME} PRIVATE ${SRC_LIB_INC_PATH})
    target_link_libraries (${TEST_NAME} ${SRC_LIB_TARGET})
endforeach ()

# Remonte la liste des cible exécutables dans le CMakeLists parent.
set (TEST_NAMES ${TEST_NAMES} PARENT_SCOPE)
