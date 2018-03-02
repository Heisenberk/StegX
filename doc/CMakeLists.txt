# Recherche de Doxygen.
find_package (Doxygen OPTIONAL_COMPONENTS dot)

# Si Doxygen est trouvé, on génère la documentation, sinon, on affiche un
# message d'erreur.
if (NOT DOXYGEN_FOUND)
    message ("-- Documentation will NOT be generated")
else ()
    # Test si le composant "dot" est présent pour la génération des graphiques.
    # Défini cette variable pour le fichier "Doxyfile.in".
    if (NOT TARGET Doxygen::dot)
        message ("-- Could NOT find dot for Doxygen")
        message ("-- Diagrams for documentation will NOT be generated with dot")
        set (DOXYGEN_HAVE_DOT NO)
    else ()
        set (DOXYGEN_HAVE_DOT YES)
    endif()

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
        DEPENDS doc-${CLI} doc-${GUI} doc-${LIB}
        )

    # Commandes de génération de la documentation.
    foreach (type ${ALL_PATH})
        set (DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/${SRC_PATH}/${type})
        set (DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${type})
        configure_file (Doxyfile.in Doxyfile-${type})
        add_custom_command (OUTPUT doc-${type}
            COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile-${type}
            COMMAND ${CMAKE_COMMAND} -E touch doc-${type}
            DEPENDS ${SRC} ${INC}
            )
    endforeach()

    # Installation de la documentation.
    get_filename_component(CMAKE_INSTALL_DOC ${CMAKE_INSTALL_DOCDIR} DIRECTORY)
    install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${LIB}
        DESTINATION ${CMAKE_INSTALL_DOC}/${PROJECT_NAME_LC}
        OPTIONAL)
endif()
