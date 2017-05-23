#need to define the version of the library
set(SOURCES index_map_tests.cpp
            dynamic_cindex_map_test.cpp 
            fixed_dim_cindex_map_test.cpp
            static_cindex_map_test.cpp
            cindex_implementation_test.cpp 
            )


set_source_files_properties(index_map_tests.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK")
add_executable(index_maps_test ${SOURCES})
target_link_libraries(index_maps_test pnicore_shared Boost::unit_test_framework)

add_logging_test("index_maps_test" index_maps_test ${PROJECT_BINARY_DIR}/test/index_maps)

