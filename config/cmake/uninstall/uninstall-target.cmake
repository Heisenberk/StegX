# S'il n'y a pas de cible uninstall présente, alors on lance la configuration.
if (NOT TARGET uninstall)
    # Variables.
    set (UNINSTALL_CMAKE_SCRIPT
        "${CMAKE_CONFIG_PATH}/uninstall/uninstall-command.cmake.in")
    set (UNINSTALL_SH_SCRIPT
        "${CMAKE_CONFIG_PATH}/uninstall/uninstall-command.sh.in")
    set (UNINSTALL_SILENT_OUTPUT "${CMAKE_BINARY_DIR}/cmake_uninstall_silent.cmake")
    set (UNINSTALL_VERBOSE_OUTPUT "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")
    set (UNINSTALL_SH_OUTPUT "${CMAKE_BINARY_DIR}/cmake_uninstall.sh")
    set (UNINSTALL_TARGET_1 uninstall)
    set (UNINSTALL_TARGET_3 dist-cleanup)

    # Cas spécial pour les UNIX, voir la cible plus bas.
    if (UNIX)
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
        add_custom_target (${UNINSTALL_TARGET_3} COMMAND ${UNINSTALL_SH_OUTPUT})
        add_dependencies (${UNINSTALL_TARGET_2} ${UNINSTALL_TARGET_1})
    else ()
        # Cible de désinstallation silencieuse multiplate-forme (cible 3). Ne
        # désinstalle que les fichiers installés, mais pas les dossiers. Utile
        # pour la désinstallation des fichiers résidus de la création des
        # packages. Pour UNIX, cette fonction est déjà assuré par la cible 2.
        set (UNINSTALL_VERBOSE false)
        configure_file ( ${UNINSTALL_CMAKE_SCRIPT} ${UNINSTALL_SILENT_OUTPUT} @ONLY)
        add_custom_target (${UNINSTALL_TARGET_3} COMMAND ${CMAKE_COMMAND} -P ${UNINSTALL_SILENT_OUTPUT})
    endif()
endif()
