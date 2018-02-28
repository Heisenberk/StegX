# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})

# Liste des dossiers contenant un header.
HEADER_DIRECTORIES(INC_DIRS)

# Binaire ======================================================================

# Nom de la cible et de l'exécutable.
set (TARGET stegx-gui)

# Sources et dépendances de l'exécutable.
add_executable (${TARGET} ${SRC} ${INC})

# Modules externes =============================================================

# Génération des tags.
if (${TAG_GEN} STREQUAL true)
    add_dependencies (${TARGET} tags-gen)
endif()

# Informations de compilation.
add_dependencies (${TARGET} display-infos)

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${TARGET} PUBLIC ${INC_DIRS} ${LIB_PUBLIC_INC_PATH})

# Bibliothèque à passer au linker.
target_link_libraries (${TARGET} ${LIB_TARGET})

# Installation =================================================================

# Déclaration de l'installation.
install (TARGETS ${TARGET}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
