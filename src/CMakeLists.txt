# Programmes externes ==========================================================

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
    endif()
endif()

# Macros =======================================================================

# Crée une liste de tout les dossiers contenant un header.
macro (HEADER_DIRECTORIES return_list)
    file (GLOB_RECURSE new_list *${INC_EXT})
    set (dir_list "")
    foreach (file_path ${new_list})
        get_filename_component (dir_path ${file_path} PATH)
        set (dir_list ${dir_list} ${dir_path})
    endforeach ()
    list (REMOVE_DUPLICATES dir_list)
    set (${return_list} ${dir_list})
endmacro ()

# Sources ======================================================================

# Extension des fichiers sources et des headers.
set (SRC_EXT .c)
set (INC_EXT .h)

# Liste tout les fichiers sources et des headers.
file (GLOB_RECURSE SRC_ALL *${SRC_EXT})
file (GLOB_RECURSE INC_ALL *${INC_EXT})

# Commandes et cibles ==========================================================

# Génération des tags.
if (${TAG_GEN} STREQUAL true)
    add_custom_target (
        tags-generate
        DEPENDS tags
        )
    add_custom_command (OUTPUT tags
        COMMAND ${TAG_GENERATOR} ${SRC_ALL} ${INC_ALL}
        COMMAND ${CMAKE_COMMAND} -E copy tags ${CMAKE_SOURCE_DIR}
        DEPENDS ${SRC_ALL} ${INC_ALL}
        )
endif()

# Message d'information.
add_custom_target (
    compil-infos
    COMMAND
        ${CMAKE_COMMAND} -E echo "[  0%] Compilation mode is set to ${CMAKE_BUILD_TYPE}"
    )

# Structure ====================================================================

# Bibliothèque
set (LIB_PATH lib)
set (LIB_PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_PATH}/inc)
add_subdirectory (${LIB_PATH})

# Interface en ligne de commande
set (CLI_PATH cli)
add_subdirectory (${CLI_PATH})

# Interface graphique
set (GUI_PATH gui)
add_subdirectory (${GUI_PATH})
