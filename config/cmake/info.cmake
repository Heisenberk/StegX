# Message d'information.
add_custom_target (
    info
    COMMAND ${CMAKE_COMMAND} -E echo_append "[INFO] "
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Compilation mode is set to ${CMAKE_BUILD_TYPE}"
    )
