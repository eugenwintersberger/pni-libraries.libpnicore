#need to define the version of the library
set(SOURCES default_dim_layout_test.cpp
            dim_algorithm_test.cpp
            dim_layout_test.cpp
            fixed_rank_dim_layout_test.cpp
            static_dim_layout.cpp
   )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(dim_layout_test ${SOURCES})
target_link_libraries(dim_layout_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(dim_layout_test ${CPPUNIT_LIBRARIES})

endif()


