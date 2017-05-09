#need to define the version of the library
set(SOURCES index_map_tests.cpp
            dynamic_cindex_map_test.cpp 
            fixed_dim_cindex_map_test.cpp
            static_cindex_map_test.cpp
            cindex_implementation_test.cpp 
            )


if(BUILD_SHARED_LIBRARIES)
    set_source_files_properties(index_map_tests.cpp PROPERTIES
                                COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK")
    add_executable(index_maps_test EXCLUDE_FROM_ALL ${SOURCES})
    target_link_libraries(index_maps_test pnicore_shared 
                                          ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})

    add_test(NAME index_maps_test 
             COMMAND index_maps_test
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             )
         message("${PROJECT_BINARY_DIR}")
             message("${BOOST_LIBRARYDIR}")
             message("${BOOST_LIBRARYDIR};$ENV{PATH}")
    set_tests_properties(index_maps_test PROPERTIES 
        ENVIRONMENT
        "$ENV{PATH}=$ENV{PATH};D:\\Development\\libpnicore-build\\src;D:\\Development\\boost-install\\lib")          
    get_test_property(index_maps_test ENVIRONMENT IMTEST_ENV)
    message("${IMTEST_ENV}")

    add_dependencies(check index_maps_test)
endif(BUILD_SHARED_LIBRARIES)


