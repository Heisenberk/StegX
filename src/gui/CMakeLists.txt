# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})

# Liste des dossiers contenant un header.
HEADER_DIRECTORIES(INC_DIRS)

# Binaires =====================================================================

# Nom de l'exécutable.
set (EXE stegx-gui)

# Dépendances de l'exécutable.
add_executable (${EXE} ${SRC} ${INC})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${EXE} PUBLIC ${INC_DIRS} ${LIB_PUBLIC})

# Bibliothèque à passer au linker.
target_link_libraries (${EXE} stegx)

# Commandes ====================================================================

add_dependencies(${EXE} tags-generate)
add_dependencies(${EXE} compil-infos)
