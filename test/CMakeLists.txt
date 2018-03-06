# Détection de la bibliothèque CMocka.
set (CMOCKA_PATH ${CMAKE_SOURCE_DIR}/${LIB_PATH}/cmocka)
find_library (CMOCKA_LIBRARY cmocka HINTS ${CMOCKA_PATH}/src)

# Si CMocka est trouvé.
if (CMOCKA_LIBRARY)
    message ("-- Found CMocka: ${CMOCKA_LIBRARY}")

    # Liste des tests et de leurs flags.
    list (APPEND tests_names "test_libsteg")
    list (APPEND tests_flags " ")

    # Cible personnalisée pour construire les tests puis les lancer.
    add_custom_target (check
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Running tests..."
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS ${tests_names}
        )

    # Déclaration de toutes les cibles correspondant aux tests.
    list (LENGTH tests_names count)
    math (EXPR count "${count} - 1")
    foreach (i RANGE ${count})
        list (GET tests_names ${i} test_name)
        list (GET tests_flags ${i} test_flags)
        add_executable (${test_name} EXCLUDE_FROM_ALL ${test_name}.c)
        target_include_directories (${test_name} PUBLIC ${CMOCKA_PATH}/include)
        target_include_directories (${test_name} PUBLIC ${CMAKE_SOURCE_DIR}/${SRC_PATH}/${LIB}/inc)
        target_link_libraries (${test_name} ${CMOCKA_LIBRARY})
        target_link_libraries (${test_name} stegx-lib)
        if (test_flags STREQUAL " ")
        else ()
            target_link_libraries (
                ${test_name}
                ${test_flags}
                )
        endif()
        add_test (NAME ${test_name} COMMAND ${test_name})
    endforeach ()

# Si CMocka n'est pas trouvé.
else ()
    message ("-- Could NOT find CMocka")
    message ("-- Tests will NOT be available")
endif()
