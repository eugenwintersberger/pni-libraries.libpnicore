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


include_directories(${Boost_INCLUDE_DIR})
link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(type_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(type_test pnicore_shared)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(type_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif()

add_executable(show_type_info EXCLUDE_FROM_ALL show_type_info.cpp)
target_link_libraries(show_type_info pnicore_shared)


add_subdirectory(conversion)
add_subdirectory(traits)

add_test(NAME type_test 
         COMMAND type_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )
add_dependencies(check type_test show_type_info)

