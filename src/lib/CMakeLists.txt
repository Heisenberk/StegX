# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})
file (GLOB_RECURSE INC_PUBLIC ${SRC_LIB_INC_PATH}/*${INC_EXT})

# Dossiers contenant un header.
# HEADER_DIRECTORIES (INC_DIRS)
set (INC_DIRS src;inc)

# Binaires =====================================================================

# Nom de la cible.
set (TARGET ${SRC_LIB_TARGET})
# Source et dépendances de la bibliothèque.
add_library (${TARGET} SHARED ${SRC} ${INC})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${TARGET} PUBLIC ${INC_DIRS})

# Installation =================================================================

# Propriétés :
# Nom de la bibliothèque.
set_target_properties (${TARGET} PROPERTIES OUTPUT_NAME ${PROJECT_NAME_LC})
# Versionnement.
set_target_properties (${TARGET} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (${TARGET} PROPERTIES SOVERSION 1)
# Headers publiques.
set_target_properties (${TARGET} PROPERTIES PUBLIC_HEADER ${INC_PUBLIC})

# Déclaration de l'installation
install (TARGETS ${TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME_LC})
