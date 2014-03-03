
#need to define the version of the library
set(TEST_SOURCES pnicoretest.cpp
                 container_utils_std_test.cpp
                 container_utils_array_test.cpp
                 math/inplace_arithmetics_test.cpp
                 math/add_operator_test.cpp
                 math/div_operator_test.cpp
                 math/sub_operator_test.cpp
                 math/mult_operator_test.cpp
                 iterator_test.cpp
                 slice_test.cpp
                 configuration_test.cpp
                 counter_test.cpp
                 index_iterator_test.cpp
                 compare.cpp
                 value_ref_test.cpp
                 value_test.cpp
                 vector_adapter_test.cpp
                 )

set(COMMON_SOURCES compare.cpp)
add_library(test_common OBJECT ${COMMON_SOURCES})

link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
add_executable(pnicoretest  ${TEST_SOURCES})
add_executable(rand_test "rand_test.cpp")
target_link_libraries(pnicoretest pnicore)
target_link_libraries(rand_test pnicore)

add_subdirectory(index_maps)
add_subdirectory(dim_layout_test)
add_subdirectory(types)
add_subdirectory(arrays)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(pnicoretest ${CPPUNIT_LIBRARIES})

endif()

if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    configure_file(pni.cfg.cmake ./test/pni.cfg)
else()
    configure_file(pni.cfg.cmake pni.cfg)
endif()

