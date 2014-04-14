#need to define the version of the library
set(SOURCES binary_test.cpp
            type_class_test.cpp
            type_id_container_test.cpp
            type_id_scalar_test.cpp
            type_info_test.cpp
            type_maps_test.cpp
            types_test.cpp
            type_str_id_test.cpp
            types_test.cpp
            container_trait_test.cpp
            bool_test.cpp
    )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(type_test ${SOURCES})
target_link_libraries(type_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(type_test ${CPPUNIT_LIBRARIES})

endif()


