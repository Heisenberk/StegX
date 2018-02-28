# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})

# Liste des dossiers contenant un header.
HEADER_DIRECTORIES(INC_DIRS)

# Binaire ======================================================================

# Nom de la cible et de l'exécutable.
set (TARGET stegx-gui)
set (GUI ${TARGET} PARENT_SCOPE)

# Sources et dépendances de l'exécutable.
add_executable (${TARGET} ${SRC} ${INC})

# Modules externes =============================================================

# Génération des tags.
if (TAG_GEN)
    add_dependencies (${TARGET} tags)
endif ()

# Informations de compilation.
add_dependencies (${TARGET} info)


# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${TARGET} PUBLIC ${INC_DIRS} ${LIB_PUBLIC_INC_PATH})

# Bibliothèque à passer au linker.
target_link_libraries (${TARGET} ${LIB_TARGET})

# Installation =================================================================

# Déclaration de l'installation.
install (TARGETS ${TARGET}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
