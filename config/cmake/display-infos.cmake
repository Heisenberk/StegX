# Message d'information.
add_custom_target (
    display-infos
    COMMAND ${CMAKE_COMMAND} -E echo "[INFO] Compilation mode is set to ${CMAKE_BUILD_TYPE}"
    )
