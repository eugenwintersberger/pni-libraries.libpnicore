#need to define the version of the library
set(SOURCES binary_test.cpp
            bool_test.cpp
            type_class_map_test.cpp
            type_id_map_test.cpp
            id_type_map_test.cpp
            container_trait_test.cpp
            type_id_test.cpp
            type_info_test.cpp
            type_id_from_str_test.cpp
            str_from_type_id_test.cpp
    )

if(BUILD_SHARED_LIBRARIES)
    set_shared_test_defs(SOURCES "testing type features")

    add_executable(type_test EXCLUDE_FROM_ALL ${SOURCES})
    target_link_libraries(type_test pnicore_shared
                                    ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})

    add_executable(show_type_info EXCLUDE_FROM_ALL show_type_info.cpp)
    target_link_libraries(show_type_info pnicore_shared)


    add_subdirectory(conversion)
    add_subdirectory(traits)

    add_test(NAME type_test 
             COMMAND type_test
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             )
    add_dependencies(check type_test show_type_info)
endif(BUILD_SHARED_LIBRARIES)

