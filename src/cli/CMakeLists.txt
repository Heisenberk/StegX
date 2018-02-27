# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})

# Liste des dossiers contenant un header.
HEADER_DIRECTORIES(INC_DIRS)

# Binaires =====================================================================

# Nom de la cible.
set (EXE stegx-cli)
# Nom de l'exécutable.
set (EXE_NAME stegx)

# Sources et dépendances de l'exécutable.
add_executable (${EXE} ${SRC} ${INC})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${EXE} PUBLIC ${INC_DIRS} ${LIB_PUBLIC})

# Bibliothèque à passer au linker.
target_link_libraries (${EXE} ${LIB})

# Commandes ====================================================================

add_dependencies (${EXE} tags-generate)
add_dependencies (${EXE} compil-infos)

# Installation =================================================================

# Nom de l'exécutable.
set_target_properties (${EXE} PROPERTIES OUTPUT_NAME ${EXE_NAME})

# Déclaration de l'installation
install (TARGETS ${EXE}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
