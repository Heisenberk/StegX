# Sources ======================================================================

# Extension des fichiers sources et des headers.
set (SRC_EXT .c)
set (SRC_EXT ${SRC_EXT} PARENT_SCOPE)
set (INC_EXT .h)
set (INC_EXT ${INC_EXT} PARENT_SCOPE)

# Structure ====================================================================

# Bibliothèque
set (LIB_PATH lib)
set (LIB ${LIB_PATH} PARENT_SCOPE)
set (LIB_PUBLIC_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_PATH}/inc)

# Interface en ligne de commande
set (CLI_PATH cli)
set (CLI ${CLI_PATH} PARENT_SCOPE)

# Interface graphique
set (GUI_PATH gui)
set (GUI ${GUI_PATH} PARENT_SCOPE)

set (ALL_PATH ${LIB_PATH} ${CLI_PATH} ${GUI_PATH})
set (ALL_PATH ${ALL_PATH} PARENT_SCOPE)

# Modules externes =============================================================

# Créer une liste de répertoires contenant des headers.
include (headers-directories)

# Informations sur la compilation.
include (info)

# Génération des tags.
include (tags)

# Installation =================================================================

# Assigne RPATH au dossier d'installation de la bibliothèque.
set (CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

# Lecture des sous-répertoires =================================================

add_subdirectory (${LIB_PATH})
add_subdirectory (${CLI_PATH})
add_subdirectory (${GUI_PATH})

# Installation supplémentaire ==================================================

# Ajoute le raccourci de l'interface graphique.
configure_file (
    ${CMAKE_SOURCE_DIR}/${DESKTOP_PATH}/${PROJECT_NAME_LC}.desktop.in
    ${CMAKE_BINARY_DIR}/${DESKTOP_PATH}/${PROJECT_NAME_LC}.desktop
    @ONLY
    )
if (EXISTS /usr/share/applications)
    install (FILES ${CMAKE_BINARY_DIR}/${DESKTOP_PATH}/${PROJECT_NAME_LC}.desktop
        DESTINATION /usr/share/applications)
    if (EXISTS /usr/share/pixmaps)
        install (FILES ${CMAKE_SOURCE_DIR}/${DESKTOP_PATH}/${PROJECT_NAME_LC}-128x128.png
            RENAME ${PROJECT_NAME_LC}.png
            DESTINATION /usr/share/pixmaps)
    endif()
endif()
