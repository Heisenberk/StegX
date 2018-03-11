# Génération des tags des sources du projet.

# Initialisation.
if (NOT TAG_GENERATOR)
    find_program (TAG_GENERATOR ctags)
    if (${TAG_GENERATOR} STREQUAL "TAG_GENERATOR-NOTFOUND")
        message ("-- Could NOT find Ctags (missing: CTAGS_EXECUTABLE)")
        message ("-- Tags will NOT be generated")
        set (TAG_GEN false)
    else ()
        message ("-- Found Ctags: ${TAG_GENERATOR}")
        set (TAG_GEN true)
    endif()
endif()

# Si Ctags est trouvé, il faut repasser ici à chaque configuration de CMake pour
# redéfinir les variables.
if (NOT ${TAG_GENERATOR} STREQUAL "TAG_GENERATOR-NOTFOUND")
    set (TAG_GEN true)
    add_custom_target (
        tags
        DEPENDS tags-${SRC_CLI_DIR} tags-${SRC_GUI_DIR} tags-${SRC_LIB_DIR}
        )
    foreach (type ${SRC_ALL_DIR})
        file (GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/${type}/*${SRC_EXT})
        file (GLOB_RECURSE INC ${CMAKE_CURRENT_SOURCE_DIR}/${type}/*${INC_EXT})
        add_custom_command (OUTPUT tags-${type}
            COMMAND ${TAG_GENERATOR} ${SRC} ${INC}
            COMMAND ${CMAKE_COMMAND} -E copy tags ${CMAKE_CURRENT_SOURCE_DIR}/${type}/tags
            COMMAND ${CMAKE_COMMAND} -E touch tags-${type}
            DEPENDS ${SRC} ${INC}
            )
    endforeach ()
endif ()
