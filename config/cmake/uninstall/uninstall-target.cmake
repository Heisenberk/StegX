if (NOT TARGET uninstall)
    # Cible de désinstallation silencieuse.
    set (UNINSTALL_VERBOSE false)
    configure_file (
        "${CMAKE_SOURCE_DIR}/${CONFIG_PATH}/uninstall/uninstall-command.cmake.in"
        "${CMAKE_BINARY_DIR}/cmake_uninstall_silent.cmake"
        @ONLY
        )
    add_custom_target (package-cleanup
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall_silent.cmake
        )
    # Cible de désinstallation verbeuse.
    set (UNINSTALL_VERBOSE true)
    configure_file (
        "${CMAKE_SOURCE_DIR}/${CONFIG_PATH}/uninstall/uninstall-command.cmake.in"
        "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
        @ONLY
        )
    add_custom_target (uninstall
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Uninstalling the project..."
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
        )
endif()
