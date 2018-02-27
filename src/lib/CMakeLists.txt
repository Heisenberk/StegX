# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})

# Liste des dossiers contenant un header.
HEADER_DIRECTORIES(INC_DIRS)

# Binaires =====================================================================

# Nom de l'exécutable.
set (LIB stegx)

# Dépendances de l'exécutable.
add_library (${LIB} SHARED ${SRC} ${INC})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${LIB} PUBLIC ${INC_DIRS} ${LIB_PUBLIC})

# Commandes ====================================================================

add_dependencies(${LIB} tags-generate)
add_dependencies(${LIB} compil-infos)
