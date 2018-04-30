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
