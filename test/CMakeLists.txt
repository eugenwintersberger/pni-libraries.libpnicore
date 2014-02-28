
#need to define the version of the library
set(TEST_SOURCES pnicoretest.cpp
                 types/type_class_test.cpp
                 types/type_info_test.cpp
                 types/type_maps_test.cpp
                 types/type_id_scalar_test.cpp
                 types/type_id_container_test.cpp
                 types/type_str_id_test.cpp
                 container_utils_std_test.cpp
                 container_utils_array_test.cpp
                 index_maps/index_map_test_common.cpp
                 index_maps/index_policy_implementation_test.cpp
                 arrays/mdarray_test.cpp
                 arrays/mdarray_unary_arithmetic_test.cpp
                 arrays/dynamic_mdarray_test.cpp
                 arrays/fix_mdarray_test.cpp
                 arrays/static_mdarray_test.cpp
                 arrays/array_selection_test.cpp
                 arrays/array_view_test.cpp
                 arrays/array_view_unary_arithmetic_test.cpp
                 arrays/scalar_test.cpp
                 math/inplace_arithmetics_test.cpp
                 math/add_operator_test.cpp
                 math/div_operator_test.cpp
                 math/sub_operator_test.cpp
                 math/mult_operator_test.cpp
                 iterator_test.cpp
                 slice_test.cpp
                 binary_test.cpp
                 configuration_test.cpp
                 counter_test.cpp
                 index_iterator_test.cpp
                 compare.cpp
                 arrays/array_test.cpp
                 value_ref_test.cpp
                 value_test.cpp
                 vector_adapter_test.cpp
                 )

set(DIM_LAYOUT_TEST_SRC dim_layout_test.cpp
                 dim_layout_test/default_dim_layout_test.cpp
                 dim_layout_test/fixed_rank_dim_layout_test.cpp)


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
add_executable(pnicoretest  ${TEST_SOURCES})
add_executable(rand_test "rand_test.cpp")
target_link_libraries(pnicoretest pnicore)
target_link_libraries(rand_test pnicore)

add_executable(dim_layout_test ${DIM_LAYOUT_TEST_SRC})
target_link_libraries(dim_layout_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(pnicoretest ${CPPUNIT_LIBRARIES})
    target_link_libraries(dim_layout_test ${CPPUNIT_LIBRARIES})

endif()

if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    configure_file(pni.cfg.cmake ./test/pni.cfg)
else()
    configure_file(pni.cfg.cmake pni.cfg)
endif()

