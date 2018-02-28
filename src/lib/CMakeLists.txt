# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})
file (GLOB_RECURSE INC_PUBLIC ${LIB_PUBLIC_INC_PATH}/*${INC_EXT})

# Liste des dossiers contenant un header.
HEADER_DIRECTORIES(INC_DIRS)

# Binaires =====================================================================

# Nom de la cible.
set (TARGET stegx-lib)
set (LIB_TARGET ${TARGET} PARENT_SCOPE)
# Nom de la bibliothèque.
set (LIB stegx)

# Source et dépendances de la bibliothèque.
add_library (${TARGET} SHARED ${SRC} ${INC})

# Modules externes =============================================================

# Génération des tags.
if (TAG_GEN)
    add_dependencies (${TARGET} tags)
endif()

# Informations de compilation.
add_dependencies (${TARGET} info)

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${TARGET} PUBLIC ${INC_DIRS})

# Installation =================================================================

# Nom de la bibliothèque.
set_target_properties (${TARGET} PROPERTIES OUTPUT_NAME ${LIB})

# Versionnement.
set_target_properties(${TARGET} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${TARGET} PROPERTIES SOVERSION 1)

# Headers publiques.
set_target_properties(${TARGET} PROPERTIES PUBLIC_HEADER ${INC_PUBLIC})

# Déclaration de l'installation
install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB})
