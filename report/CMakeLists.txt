# Recherche de LaTeX.
find_package (LATEX COMPONENTS PDFLATEX)

# Si LaTeX est trouvé, on génère le rapport, sinon, on affiche un message
# d'erreur.
if (NOT LATEX_FOUND OR NOT LATEX_PDFLATEX_FOUND)
    message ("-- Report will NOT be generated")
else ()
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
endif()
