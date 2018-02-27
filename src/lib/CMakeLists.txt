# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})
file (GLOB_RECURSE INC_PUBLIC ${LIB_PUBLIC}/*${INC_EXT})

# Liste des dossiers contenant un header.
HEADER_DIRECTORIES(INC_DIRS)

# Binaires =====================================================================

# Nom de la bibliothèque.
set (LIB stegx-lib)
set (LIB stegx-lib PARENT_SCOPE)

# Dépendances de l'exécutable.
add_library (${LIB} SHARED ${SRC} ${INC})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${LIB} PUBLIC ${INC_DIRS})

# Commandes ====================================================================

add_dependencies(${LIB} tags-generate)
add_dependencies(${LIB} compil-infos)

# Installation =================================================================

# Versionnement
set_target_properties(${LIB} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${LIB} PROPERTIES SOVERSION 1)

# Headers publiques
set_target_properties(${LIB} PROPERTIES PUBLIC_HEADER ${INC_PUBLIC})

# Déclaration de l'installation
install(TARGETS ${LIB}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
