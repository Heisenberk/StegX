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
    
    # Flags de liaison.
    # Sur Windows, n'affiche pas la console lors du lancement de l'application.
    if (WIN32)
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
    endif ()

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
    
    # Ajoute un raccourci.
    if (UNIX)
        set (DESKTOP_PATH_OUTPUT
            ${CMAKE_BINARY_DIR}/${CONFIG_DIR}/${CMAKE_CONFIG_DIR}/${DESKTOP_DIR})
        configure_file (
            ${DESKTOP_PATH}/${PROJECT_NAME_LC}.desktop.in
            ${DESKTOP_PATH_OUTPUT}/${PROJECT_NAME_LC}.desktop
            @ONLY
            )
        set (DESKTOP_INSTALL_DIR /usr/share/applications)
        set (ICON_INSTALL_DIR /usr/share/pixmaps)
        if (EXISTS ${DESKTOP_INSTALL_DIR})
            install (FILES ${DESKTOP_PATH_OUTPUT}/${PROJECT_NAME_LC}.desktop
                DESTINATION ${DESKTOP_INSTALL_DIR})
            if (EXISTS ${ICON_INSTALL_DIR})
                install (FILES ${DESKTOP_PATH}/${PROJECT_NAME_LC}-128x128.png
                    RENAME ${PROJECT_NAME_LC}.png
                    DESTINATION ${ICON_INSTALL_DIR})
            endif()
        endif()
    elseif (WIN32)
        install (FILES ${DESKTOP_PATH}/${PROJECT_NAME_LC}-64x64.ico
            RENAME ${PROJECT_NAME_LC}.ico
            DESTINATION ./
            COMPONENT ${SRC_GUI_COMP})
    endif ()
    
    # Copies les DLL de GTK+ dans le dossier bin de l'installation sur Windows.
    if (WIN32)
        set (GTK_RUNTIME_DIR gtk+/win)
        set (GTK_RUNTIME_PATH ${CMAKE_SOURCE_DIR}/${LIB_DIR}/${GTK_RUNTIME_DIR})
        set (GTK_RUNTIME_BIN_DIR bin)
        file (GLOB_RECURSE GTK_RUNTIME_LIBS ${GTK_RUNTIME_PATH}/${GTK_RUNTIME_BIN_DIR}/*)
        install (FILES ${GTK_RUNTIME_LIBS}
            DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT ${SRC_GUI_COMP}
            )
    endif ()
endif ()
