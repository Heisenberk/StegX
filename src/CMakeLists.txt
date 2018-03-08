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
set (CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR};../${CMAKE_INSTALL_LIBDIR})

# Ajoute le raccourci de l'interface graphique.
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

# Liste des générateurs.
set (CPACK_GENERATOR STGZ;TGZ;DEB)

# Configuration pour DEB.
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "AYOUB Pierre, BASKEVITCH Claire, BESSAC Tristan, CAUMES Clément, DELAUNAY Damien, DOUDOUH Yassin")

# Lance la configuration de CPack.
include (CPack)

# Cible personnalisée pour créer les packages (pour mettre les cibles en
# dépendances et lancer une désinstallation complète contre les fichiers
# résidus).
add_custom_target (dist
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Run CPack packaging tool..."
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} ${CMAKE_CPACK_COMMAND} --config CPackConfig.cmake
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target dist-cleanup
    DEPENDS ${SRC_ALL_TARGETS}
    )
