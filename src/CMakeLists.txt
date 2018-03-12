# Modules externes =============================================================

# Informations sur la compilation.
include (info)
# Génération des tags des fichiers sources.
include (tags)

# Installation =================================================================

# Cible de désinstallation.
include (uninstall-target)

# Dossiers standards GNU pour l'installation.
include (GNUInstallDirs)

# Assigne RPATH au dossier d'installation de la bibliothèque.
if (UNIX)
    set (CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR};
    ./${CMAKE_INSTALL_LIBDIR};../${CMAKE_INSTALL_LIBDIR})
endif()

# Ajoute un raccourci pour l'interface graphique sur les UNIX.
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
endif()

# Communs ======================================================================

# Noms des différents composants :
# Bibliothèque StegX.
set (SRC_LIB_COMP "library_stegx")
# Interface en ligne de commande.
set (SRC_CLI_COMP "interface_command_line")
# Interface graphique.
set (SRC_GUI_COMP "interface_graphical")

# Lecture des sous-répertoires.
add_subdirectory (${SRC_LIB_DIR})
add_subdirectory (${SRC_CLI_DIR})
add_subdirectory (${SRC_GUI_DIR})

# Ajout des modules externes en dépendances sur les cibles.
foreach (target ${SRC_ALL_TARGETS})
    # Génération des tags.
    if (TAG_GEN)
        add_dependencies (${target} tags)
    endif()
    # Informations de compilation.
    add_dependencies (${target} info)
endforeach ()

# Package ======================================================================

if (UNIX)
    # Liste des générateurs.
    set (CPACK_GENERATOR TGZ;DEB;STGZ)
    # Configuration pour DEB.
    set (CPACK_DEBIAN_PACKAGE_MAINTAINER "AYOUB Pierre, BASKEVITCH Claire, BESSAC Tristan, CAUMES Clément, DELAUNAY Damien, DOUDOUH Yassin")
elseif (WIN32)
    # Liste des générateurs.
    set (CPACK_GENERATOR ZIP;NSIS)
    # Configuration pour NSIS.
    
endif ()

if (UNIX OR WIN32)
    # Répertoire de destination.
    set (PACKAGE_TARGET dist)
    set (CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/${PACKAGE_TARGET})

    # License.
    set (PROJECT_FILE_LICENSE COPYING)
    set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/${PROJECT_FILE_LICENSE})

    # Lance la configuration de CPack.
    include (CPack)
    
    # Composants :
    # Bibliothèque StegX.
    cpack_add_component(${SRC_LIB_COMP}
        DISPLAY_NAME "Bibliotheque StegX"
        DESCRIPTION "Bibliotheque StegX de Steganographie."
        REQUIRED
        )
    # Interface en ligne de commande.
    cpack_add_component(${SRC_CLI_COMP}
        DISPLAY_NAME "Interface en ligne de commande"
        DESCRIPTION "Interface en ligne de commande permettant d'utiliser la bibliotheque StegX."
        )
    # Interface graphique.
    cpack_add_component(${SRC_GUI_COMP}
        DISPLAY_NAME "Interface graphique"
        DESCRIPTION "Interface graphique permettant d'utiliser la bibliotheque StegX."
        )
    
    # Cible personnalisée pour créer les packages (pour mettre les cibles en
    # dépendances et lancer une désinstallation complète contre les fichiers
    # résidus).
    add_custom_target (${PACKAGE_TARGET}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target package
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target dist-cleanup
        DEPENDS ${SRC_ALL_TARGETS}
        )
endif ()
