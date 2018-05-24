# Répertoires concernant CMocka.
set (CMOCKA_DIR cmocka)
if (WIN32)
    set (CMOCKA_DIR_OS win/msvc)
else ()
    set (CMOCKA_DIR_OS unix)
endif ()
set (CMOCKA_PATH ${CMAKE_SOURCE_DIR}/${LIB_DIR}/${CMOCKA_DIR}/${CMOCKA_DIR_OS})
set (CMOCKA_INC_DIR include)
set (CMOCKA_LIB_DIR lib)
set (CMOCKA_BIN_DIR bin)

# Détection de la bibliothèque CMocka.
if (NOT CMOCKA_LIBRARY)
    # Recherche de la bibliothèque.
    find_library (CMOCKA_LIBRARY cmocka HINTS ${CMOCKA_PATH}/${CMOCKA_LIB_DIR})
    # Messages d'informations.
    if (${CMOCKA_LIBRARY} STREQUAL "CMOCKA_LIBRARY-NOTFOUND")
        message ("-- Could NOT find CMocka (missing: CMOCKA_LIBRARY)")
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
# Auteur : Pierre AYOUB
# ==============================================================================

    # Liste des répertoires contenant les tests.
    # SUBDIRLIST (TEST_ALL_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set (TEST_ALL_DIR ${SRC_LIB_DIR})

    # Listes des sous-cibles de test.
    foreach (dir ${TEST_ALL_DIR})
        list (APPEND TEST_TARGETS ${TEST_TARGET}-${dir})
    endforeach ()
    # Cible personnalisée pour construire les tests puis les lancer.
    add_custom_target (${TEST_TARGET}
        DEPENDS ${TEST_TARGETS}
        )
    
    # Windows : Copie la DLL de CMocka dans le répertoire des tests pour le
    # linkage à l'exécution.
    if (WIN32)
        get_filename_component (CMOCKA_LIBRARY_NAME ${CMOCKA_LIBRARY} NAME_WE)
        set (CMOCKA_LIB_DLL_PATH "${CMOCKA_PATH}/${CMOCKA_BIN_DIR}/${CMOCKA_LIBRARY_NAME}.dll")
        add_custom_command (TARGET ${TEST_TARGET} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMOCKA_LIB_DLL_PATH} ${TEST_OUTPUT_PATH}/$<IF:$<CONFIG:Debug>,Debug,Release>/${CMOCKA_LIBRARY_NAME}.dll
            )
    endif ()

    # Création des sous-cibles de test, puis lecture des tests.
    foreach (dir ${TEST_ALL_DIR})
        # Lecture du répertoire.
        add_subdirectory (${dir})
        # Sous-cible personnalisée avec dépendances sur les cibles de test exécutable.
        add_custom_command (OUTPUT ${TEST_TARGET}-${dir}
            COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Running tests for ${dir}..."
            COMMAND ${CMAKE_COMMAND} -E chdir ${dir} ${CMAKE_CTEST_COMMAND} -C $<IF:$<CONFIG:Debug>,Debug,Release> --output-on-failure
            COMMAND ${CMAKE_COMMAND} -E touch ${TEST_TARGET}-${dir}
            DEPENDS ${TEST_NAMES}
            )
        # Windows : Regroupement des tests dans un même dossier.
        if (WIN32)
            foreach (target ${TEST_NAMES})
                set_target_properties (${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_PATH})
            endforeach ()
        endif()
        # Nettoyage.
        set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
            ${dir}/Testing
            )
    endforeach ()
endif()
