# Sources ======================================================================

# Extension des fichiers sources et des headers.
set (SRC_EXT .c)
set (INC_EXT .h)

# Modules externes =============================================================

# Créer une liste de répertoires contenant des headers.
include (headers-directories)

# Informations sur la compilation.
include (display-infos)

# Génération des tags.
include (tags-gen)

# Installation =================================================================

# Cible de désinstallation.
include (uninstall-target)

# Dossiers standards GNU pour l'installation.
include (GNUInstallDirs)

# Assigne RPATH au dossier d'installation de la bibliothèque.
set (CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

# Structure ====================================================================

# Bibliothèque
set (LIB_PATH lib)
set (LIB_PUBLIC_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_PATH}/inc)
add_subdirectory (${LIB_PATH})

# Interface en ligne de commande
set (CLI_PATH cli)
add_subdirectory (${CLI_PATH})

# Interface graphique
set (GUI_PATH gui)
add_subdirectory (${GUI_PATH})

# Installation supplémentaires =================================================

# Ajoute le raccourci de l'interface graphique.
configure_file (
    ${CMAKE_SOURCE_DIR}/${CONFIG_PATH}/stegx.desktop.in
    ${CMAKE_BINARY_DIR}/stegx.desktop
    @ONLY
    )
if (EXISTS /usr/share/applications)
    install (FILES ${CMAKE_BINARY_DIR}/stegx.desktop
        DESTINATION /usr/share/applications)
endif()
