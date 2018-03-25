# S'il n'y a pas de cible uninstall présente, alors on lance la configuration.
if (NOT TARGET uninstall)
    # Fichiers en entré.
    set (UNINSTALL_CMAKE_SCRIPT
        "${CMAKE_TARGET_UNINSTALL_PATH}/uninstall-command.cmake.in")
    set (UNINSTALL_SH_SCRIPT
        "${CMAKE_TARGET_UNINSTALL_PATH}/uninstall-command.sh.in")
    set (UNINSTALL_BAT_SCRIPT
        "${CMAKE_TARGET_UNINSTALL_PATH}/uninstall-command.bat.in")
        
    # Fichiers en sortit.
    set (UNINSTALL_SILENT_OUTPUT "${CMAKE_BINARY_DIR}/cmake_uninstall_silent.cmake")
    set (UNINSTALL_VERBOSE_OUTPUT "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")
    set (UNINSTALL_SH_OUTPUT "${CMAKE_BINARY_DIR}/cmake_uninstall.sh")
    set (UNINSTALL_BAT_OUTPUT "${CMAKE_BINARY_DIR}/cmake_uninstall.bat")
    
    # Noms des cibles.
    set (UNINSTALL_TARGET_1 uninstall)
    set (UNINSTALL_TARGET_3 dist-cleanup)
    # Cas spécial pour les UNIX et Windows, voir les cibles plus bas.
    if (UNIX OR WIN32)
        set (UNINSTALL_TARGET_1 uninstall-files)
        set (UNINSTALL_TARGET_2 uninstall)
    endif()

    # Cible de désinstallation verbeuse multiplate-forme (cible 1). Ne
    # désinstalle que les fichiers installés, mais pas les dossiers.
    set (UNINSTALL_VERBOSE true)
    configure_file ( ${UNINSTALL_CMAKE_SCRIPT} ${UNINSTALL_VERBOSE_OUTPUT} @ONLY)
    add_custom_target (${UNINSTALL_TARGET_1}
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Uninstalling the project..."
        COMMAND ${CMAKE_COMMAND} -P ${UNINSTALL_VERBOSE_OUTPUT}
        )

    # Cible de désinstallation silencieuse uniquement pour UNIX (cible 2).
    # Désinstalle les fichiers et les dossiers installés.
    if (UNIX)
        configure_file (${UNINSTALL_SH_SCRIPT} ${UNINSTALL_SH_OUTPUT} @ONLY)
        add_custom_target (${UNINSTALL_TARGET_2} COMMAND ${UNINSTALL_SH_OUTPUT})
        # Donne à l'utilisateur les permissions sur les fichiers crées lors de
        # la création des packages en plus de désinstaller les résidus.
        add_custom_target (${UNINSTALL_TARGET_3} COMMAND ${UNINSTALL_SH_OUTPUT}
            COMMAND sudo chown $ENV{USER}:$ENV{USER} -R ${CPACK_PACKAGE_DIRECTORY} ${CMAKE_BINARY_DIR}/install_manifest.txt)
        add_dependencies (${UNINSTALL_TARGET_2} ${UNINSTALL_TARGET_1})
    # Cible de désinstallation silencieuse uniquement pour Windows (cible 2).
    # Désinstalle les fichiers et les dossiers installés.
    elseif (WIN32)
        configure_file (${UNINSTALL_BAT_SCRIPT} ${UNINSTALL_BAT_OUTPUT} @ONLY)
        add_custom_target (${UNINSTALL_TARGET_2} COMMAND ${UNINSTALL_BAT_OUTPUT})
        add_custom_target (${UNINSTALL_TARGET_3})
        add_dependencies (${UNINSTALL_TARGET_2} ${UNINSTALL_TARGET_1})
    # Cible de désinstallation silencieuse multiplate-forme (cible 3). Ne
    # désinstalle que les fichiers installés, mais pas les dossiers. Utile
    # pour la désinstallation des fichiers résidus de la création des
    # packages. Pour UNIX et Windows, cette fonction est déjà assuré par la cible 2.
    else ()
        set (UNINSTALL_VERBOSE false)
        configure_file ( ${UNINSTALL_CMAKE_SCRIPT} ${UNINSTALL_SILENT_OUTPUT} @ONLY)
        add_custom_target (${UNINSTALL_TARGET_3} COMMAND ${CMAKE_COMMAND} -P ${UNINSTALL_SILENT_OUTPUT})
    endif()
endif()
