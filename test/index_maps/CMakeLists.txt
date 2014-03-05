#need to define the version of the library
set(SOURCES index_maps_test.cpp
            index_map_test_common.cpp 
            cindex_implementation_test.cpp )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(index_maps_test ${SOURCES})
target_link_libraries(index_maps_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(index_maps_test ${CPPUNIT_LIBRARIES})

endif()


