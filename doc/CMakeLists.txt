# Génération de la documentation du projet.

# Répertoire contenant les variables de configuration.
set (DOXYGEN_VAR_DIR var)
set (DOXYGEN_VAR_PATH ${CMAKE_CURRENT_BINARY_DIR}/var)

# Initialisation.
if (NOT DEFINED DOXYGEN_EXECUTABLE)
    # Recherche de Doxygen.
    find_package (Doxygen OPTIONAL_COMPONENTS dot)
    if (NOT DOXYGEN_EXECUTABLE)
        message ("-- Documentation will NOT be generated")
    # Test si le composant "dot" est présent pour la génération des graphiques.
    # Défini cette variable pour le fichier "Doxyfile.in".
    elseif (NOT TARGET Doxygen::dot)
        message ("-- Diagrams for documentation will be generated but NOT with dot")
        file (WRITE ${DOXYGEN_VAR_PATH}/DOXYGEN_HAVE_DOT NO)
    else ()
        file (WRITE ${DOXYGEN_VAR_PATH}/DOXYGEN_HAVE_DOT YES)
    endif()
endif ()

# Si Doxygen est trouvé.
if (DOXYGEN_EXECUTABLE)
    # Lecture des variables (nécéssaire car si elles sont initalisées dans le
    # bloc d'initalisation, elles sont supprimées lors d'une regénération de CMake).
    ## Variables concernant le composant dot.
    file (READ ${DOXYGEN_VAR_PATH}/DOXYGEN_HAVE_DOT DOXYGEN_HAVE_DOT)
    if (${DOXYGEN_HAVE_DOT} STREQUAL NO)
        set (DOXYGEN_DOT_EXECUTABLE "")
    endif ()

    # Dossier et nom du logo de la documentation.
    set (DOC_LOGO_DIR rsc)
    set (DOC_LOGO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${DOC_LOGO_DIR})
    set (DOC_LOGO_NAME logo-doc.png)

    # Si on est en mode Release, la documentation est générée automatiquement et
    # les messages de warnings/d'errurs sont désactivés. Si on est en mode
    # Debug, les messages de warnings/d'erreurs sont activés.
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set (MODE ALL)
        set (WARNINGS NO)
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set (WARNINGS YES)
    endif()

    # Cible de génération de la documentation.
    add_custom_target (doc ${MODE}
        DEPENDS doc-${SRC_CLI_DIR} doc-${SRC_GUI_DIR} doc-${SRC_LIB_DIR}
        )

    # Commandes de génération de la documentation.
    foreach (type ${SRC_ALL_DIR})
        set (DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${type})
        set (DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${type})
        file (GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${type}/*${SRC_EXT})
        file (GLOB_RECURSE INC ${CMAKE_SOURCE_DIR}/${SRC_DIR}/${type}/*${INC_EXT})
        set (DOC_LOG_ERROR_NAME errors-${type}.log)
        list (APPEND DOC_LOG_ERROR_LIST ${DOC_LOG_ERROR_NAME})
        configure_file (Doxyfile.in Doxyfile-${type} @ONLY)
        add_custom_command (OUTPUT doc-${type}
            COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile-${type}
            COMMAND ${CMAKE_COMMAND} -E touch doc-${type}
            DEPENDS ${SRC} ${INC} ${CMAKE_SOURCE_DIR}/README.md
            )
    endforeach()

    # Nettoyage.
    set_property (DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        ${DOC_LOG_ERROR_LIST} ${SRC_ALL_DIR}
        )

    # Installation de la documentation.
    include (GNUInstallDirs)
    get_filename_component (CMAKE_INSTALL_DOC ${CMAKE_INSTALL_DOCDIR} DIRECTORY)
    install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${SRC_LIB_DIR}
        DESTINATION ${CMAKE_INSTALL_DOC}/${PROJECT_NAME_LC}
        OPTIONAL)
endif()
