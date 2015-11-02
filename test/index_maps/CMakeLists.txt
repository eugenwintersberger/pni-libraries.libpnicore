#need to define the version of the library
set(SOURCES index_map_tests.cpp
            dynamic_cindex_map_test.cpp 
            fixed_dim_cindex_map_test.cpp
            static_cindex_map_test.cpp
            cindex_implementation_test.cpp 
            )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_definitions(-DBOOST_TEST_NO_MAIN)
add_executable(index_maps_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(index_maps_test pnicore ${Boost_LIBRARIES})

add_test(NAME index_maps_test 
         COMMAND index_maps_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )

add_dependencies(check index_maps_test)


