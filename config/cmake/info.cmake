# Message d'information.
add_custom_target (
    info
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "[INFO] Compilation mode is set to ${CMAKE_BUILD_TYPE}"
    )
