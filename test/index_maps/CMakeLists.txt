#need to define the version of the library
set(SOURCES 
            #index_maps_test.cpp
            #index_map_test_common.cpp 
            cindex_implementation_test.cpp )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(index_maps_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(index_maps_test pnicore)

add_test(NAME index_maps_test 
         COMMAND index_maps_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )

     #add_dependencies(check index_maps_test)


