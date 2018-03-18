# GTK+ ==========================================================================

# Initialisation.
if (NOT DEFINED PKG_CONFIG_FOUND)
    # Initialise Pkg-Config.
    include (FindPkgConfig)
    # Si Pkg-Config est trouvé, on l'utilise pour trouver GTK+.
    if (PKG_CONFIG_FOUND)
        pkg_check_modules (GTK "gtk+-3.0")
    endif ()
    # Si Pkg-Config ou GTK+ sont absents, alors on affiche un message
    # d'avertissement.
    if (NOT PKG_CONFIG_FOUND OR NOT GTK_FOUND)
        message ("-- Target ${SRC_GUI_TARGET} for graphical user interface will NOT be available")
    endif ()
endif ()

# Si on à trouvé GTK+.
if (GTK_FOUND)
    # Sources ==================================================================

    # Liste des fichiers sources et des headers.
    file (GLOB_RECURSE SRC *${SRC_EXT})
    file (GLOB_RECURSE INC *${INC_EXT})

    # Dossiers contenant un header.
    # HEADER_DIRECTORIES(INC_DIRS)
    set (INC_DIRS ./)

    # Binaire ==================================================================

    # Nom de la cible et de l'exécutable.
    set (TARGET ${SRC_GUI_TARGET})
    # Sources et dépendances de l'exécutable.
    add_executable (${TARGET} ${SRC} ${INC})

    # Compilation ==============================================================

    # Flags de compilation.
    target_compile_options (${TARGET} PUBLIC ${GTK_CFLAGS})

    # Dossiers des headers à inclure pour le préprocesseur.
    target_include_directories (${TARGET} PUBLIC
        ${INC_DIRS} ${SRC_LIB_INC_PATH} ${GTK_INCLUDE_DIRS})

    # Bibliothèque à passer au linker.
    target_link_libraries (${TARGET} ${SRC_LIB_TARGET} ${GTK_LDFLAGS})

    # Installation =============================================================

    # Déclaration de l'installation.
    install (TARGETS ${TARGET}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ${SRC_GUI_COMP}
            )
endif ()
