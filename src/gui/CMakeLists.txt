# GTK+ ==========================================================================

# Initialisation.
if (NOT DEFINED PKG_CONFIG_FOUND AND NOT GTK_FOUND)
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
    # Configuration ============================================================
    
    # Chemin de l'icône du programme.
    set (ICON_INSTALL_NAME ${PROJECT_NAME_LC}.png)
    if (UNIX)
        set (DESKTOP_INSTALL_DIR /usr/share/applications)
        set (ICON_INSTALL_DIR /usr/share/pixmaps)
    elseif (WIN32)
        set (ICON_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
    endif ()
    
    # Message d'avertissement du header.
    set (INC_CONFIG_WARN_MSG
        "Ne pas éditer ce fichier ! Génération automatique par CMake lors de 
        la configuration du build."
        )

    # Génération du header.
    set (INC_CONFIG_NAME config.h)
    set (INC_CONFIG_DIR common)
    set (INC_CONFIG_IN_FPATH ${CMAKE_CURRENT_SOURCE_DIR}/${INC_CONFIG_DIR}/${INC_CONFIG_NAME}.in)
    set (INC_CONFIG_OUT_FPATH ${CMAKE_CURRENT_BINARY_DIR}/${INC_CONFIG_DIR}/${INC_CONFIG_NAME})
    configure_file (${INC_CONFIG_IN_FPATH} ${INC_CONFIG_OUT_FPATH} @ONLY)

    # Commande pour regénérer le header si besoin.
    add_custom_command (OUTPUT ${INC_CONFIG_OUT_FPATH}
        COMMAND ${CMAKE_COMMAND} ${CMAKE_BINARY_DIR}
        DEPENDS ${INC_CONFIG_IN_FPATH}
        )

    # Nettoyage.
    set_property (DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${INC_CONFIG_DIR}
        )

    # Sources ==================================================================

    # Liste des fichiers sources et des headers.
    file (GLOB_RECURSE SRC *${SRC_EXT})
    file (GLOB_RECURSE INC *${INC_EXT})

    # Dossiers contenant un header.
    # HEADER_DIRECTORIES (INC_DIRS)
    set (INC_DIRS ./ ${CMAKE_CURRENT_BINARY_DIR})

    # Binaire ==================================================================

    # Nom de la cible et de l'exécutable.
    set (TARGET ${SRC_GUI_TARGET})
    # Sources et dépendances de l'exécutable.
    add_executable (${TARGET} ${SRC} ${INC} ${INC_CONFIG_OUT_FPATH})

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
    
    # Ajoute un raccourci et une icône pour la GUI.
    if (UNIX)
        set (DESKTOP_PATH_OUTPUT
            ${CMAKE_BINARY_DIR}/${CONFIG_DIR}/${CMAKE_CONFIG_DIR}/${DESKTOP_DIR})
        configure_file (
            ${DESKTOP_PATH}/${PROJECT_NAME_LC}.desktop.in
            ${DESKTOP_PATH_OUTPUT}/${PROJECT_NAME_LC}.desktop
            @ONLY
            )
        if (EXISTS ${DESKTOP_INSTALL_DIR})
            install (FILES ${DESKTOP_PATH_OUTPUT}/${PROJECT_NAME_LC}.desktop
                DESTINATION ${DESKTOP_INSTALL_DIR})
            if (EXISTS ${ICON_INSTALL_DIR})
                install (FILES ${DESKTOP_PATH}/${PROJECT_NAME_LC}-128x128.png
                    RENAME ${ICON_INSTALL_NAME}
                    DESTINATION ${ICON_INSTALL_DIR})
            endif()
        endif()
    elseif (WIN32)
        install (FILES ${DESKTOP_PATH}/${PROJECT_NAME_LC}-64x64.png
            DESTINATION ./
            RENAME ${ICON_INSTALL_NAME}
            COMPONENT ${SRC_GUI_COMP})
        install (FILES ${DESKTOP_PATH}/${PROJECT_NAME_LC}-64x64.ico
            DESTINATION ./
            RENAME ${PROJECT_NAME_LC}.ico
            COMPONENT ${SRC_GUI_COMP})
    endif ()
    
    # Copie les ressources d'exécution de GTK+ dans le dossier l'installation sur Windows.
    if (WIN32)
        set (GTK_RUNTIME_DIR gtk+/win)
        set (GTK_RUNTIME_PATH ${CMAKE_SOURCE_DIR}/${LIB_DIR}/${GTK_RUNTIME_DIR})
        set (GTK_RUNTIME_NAME_WE gtk+)
        set (GTK_RUNTIME_NAME ${GTK_RUNTIME_NAME_WE}.zip)
        install (CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E make_directory \"${CMAKE_BINARY_DIR}/${LIB_DIR}\") \n \
                       execute_process(COMMAND \"${CMAKE_COMMAND}\" -E chdir \"${CMAKE_BINARY_DIR}/${LIB_DIR}\" \"${CMAKE_COMMAND}\" -E tar xf \"${GTK_RUNTIME_PATH}/${GTK_RUNTIME_NAME}\")"
            COMPONENT ${SRC_GUI_COMP}
            )
        install (DIRECTORY ${CMAKE_BINARY_DIR}/${LIB_DIR}/${GTK_RUNTIME_NAME_WE}/ DESTINATION ./
            COMPONENT ${SRC_GUI_COMP}
            PATTERN "${CMAKE_BINARY_DIR}/lib/gtk+/*"
            )
        # Nettoyage.
        set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
            ${CMAKE_BINARY_DIR}/${LIB_DIR}
            )
    endif ()
endif ()
