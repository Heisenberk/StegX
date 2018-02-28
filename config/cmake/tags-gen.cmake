# Génération des tags des sources du projet.
if (NOT TAG_GENERATOR)
    find_program (TAG_GENERATOR ctags)
    if (${TAG_GENERATOR} STREQUAL "TAG_GENERATOR-NOTFOUND")
        message ("-- Could NOT find Ctags")
        message ("-- Tags will NOT be generated")
        set (TAG_GEN false)
    else ()
        message ("-- Found Ctags: ${TAG_GENERATOR}")
        set (TAG_GEN true)
        add_custom_target (
            tags-gen
            DEPENDS tags-cli tags-gui tags-lib
            )
        foreach (type cli gui lib)
            file (GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/${type}/*${SRC_EXT})
            file (GLOB_RECURSE INC ${CMAKE_CURRENT_SOURCE_DIR}/${type}/*${INC_EXT})
            add_custom_command (OUTPUT tags-${type}
                COMMAND ${TAG_GENERATOR} ${SRC} ${INC}
                COMMAND ${CMAKE_COMMAND} -E copy tags ${CMAKE_CURRENT_SOURCE_DIR}/${type}/tags
                DEPENDS ${SRC} ${INC}
                )
        endforeach()
    endif()
endif()
