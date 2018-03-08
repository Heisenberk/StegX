# Sources ======================================================================

# Liste des fichiers sources et des headers.
file (GLOB_RECURSE SRC *${SRC_EXT})
file (GLOB_RECURSE INC *${INC_EXT})

# Dossiers contenant un header.
# HEADER_DIRECTORIES(INC_DIRS)
set (INC_DIRS ./)

# Binaire ======================================================================

# Nom de la cible et de l'exécutable.
set (TARGET ${SRC_GUI_TARGET})
# Sources et dépendances de l'exécutable.
add_executable (${TARGET} ${SRC} ${INC})

# Compilation ==================================================================

# Dossiers des headers à inclure pour le préprocesseur.
target_include_directories (${TARGET} PUBLIC ${INC_DIRS} ${SRC_LIB_INC_PATH})

# Bibliothèque à passer au linker.
target_link_libraries (${TARGET} ${SRC_LIB_TARGET})

# Installation =================================================================

# Déclaration de l'installation.
install (TARGETS ${TARGET}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
