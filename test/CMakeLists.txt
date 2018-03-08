# Détection de la bibliothèque CMocka.
if (NOT CMOCKA_LIBRARY)
    # Variables.
    set (CMOCKA_DIR cmocka)
    set (CMOCKA_PATH ${CMAKE_SOURCE_DIR}/${LIB_DIR}/${CMOCKA_DIR})
    set (CMOCKA_INC_DIR include)
    # Recherche de la bibliothèque.
    find_library (CMOCKA_LIBRARY cmocka HINTS ${CMOCKA_PATH}/src)
    # Messages d'informations.
    if (${CMOCKA_LIBRARY} STREQUAL "CMOCKA_LIBRARY-NOTFOUND")
        message ("-- Could NOT find CMocka")
        message ("-- Unit Tests will NOT be available")
    else ()
        message ("-- Found CMocka: ${CMOCKA_LIBRARY}")
    endif()
endif()

# Si CMocka est trouvé.
if (CMOCKA_LIBRARY)
    # Extension des fichiers contenant les flags persos.
    set (FLAG_EXT flag)
    # Nom de la cible de test.
    set (TEST_TARGET check)
    # Liste des répertoires contenant les tests.
    SUBDIRLIST (TEST_ALL_DIR ${CMAKE_CURRENT_SOURCE_DIR})

    # Listes des sous-cibles de test.
    foreach (dir ${TEST_ALL_DIR})
        list (APPEND TEST_TARGETS ${TEST_TARGET}-${dir})
    endforeach ()
    # Cible personnalisée pour construire les tests puis les lancer.
    add_custom_target (${TEST_TARGET}
        DEPENDS ${TEST_TARGETS}
        )

    # Création des sous-cibles de test, puis lecture des tests.
    foreach (dir ${TEST_ALL_DIR})
        # Lecture du répertoire.
        add_subdirectory (${dir})
        # Sous-cible personnalisée avec dépendances sur les cibles de test exécutable.
        add_custom_command (OUTPUT ${TEST_TARGET}-${dir}
            COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Running tests for ${dir}..."
            COMMAND ${CMAKE_COMMAND} -E chdir ${dir} ${CMAKE_CTEST_COMMAND} --output-on-failure
            COMMAND ${CMAKE_COMMAND} -E touch ${TEST_TARGET}-${dir}
            DEPENDS ${TEST_NAMES}
            )
    endforeach ()
endif()
