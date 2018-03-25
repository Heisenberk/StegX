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
        endif()
    endif()

    # Variables
    SUBDIRLIST(LATEX_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

    # Cible de génération des rapports.
    add_custom_target (report ${MODE} DEPENDS ${LATEX_DIRS})

    # Commandes de génération de chaque rapport.
    foreach(subdir ${LATEX_DIRS})
        set (LATEX_CURR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        set (LATEX_INPUT ${LATEX_CURR_DIR}/${subdir}.tex)
        set (LATEX_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${subdir})
        add_custom_command (OUTPUT ${LATEX_OUTPUT}
                COMMAND ${CMAKE_COMMAND} -E make_directory ${LATEX_OUTPUT}
                COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_CURR_DIR}
                    ${PDFLATEX_COMPILER} -output-directory ${LATEX_OUTPUT}
                    ${LATEX_INPUT} ${OUTPUT_OPTIONS}
                DEPENDS ${LATEX_INPUT}
                )
    endforeach()

    # Nettoyage.
    set_property (DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        ${LATEX_DIRS}
        )
endif()
