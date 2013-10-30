
#need to define the version of the library
set(TEST_SOURCES pnicoretest.cpp
                 types/type_class_test.cpp
                 types/type_info_test.cpp
                 types/type_maps_test.cpp
                 types/type_id_scalar_test.cpp
                 types/type_id_container_test.cpp
                 types/type_str_id_test.cpp
                 index_maps/index_map_test_common.cpp
                 arrays/mdarray_test.cpp
                 arrays/dynamic_mdarray_test.cpp
                 arrays/fix_mdarray_test.cpp
                 arrays/static_mdarray_test.cpp
                 arrays/array_selection_test.cpp
                 compare.cpp
                 )
#add_operator_test.cpp
#array_selection_test.cpp
#array_test.cpp
#array_view_selector_test.cpp
#array_view_test.cpp
#binary_test.cpp
#configuration_test.cpp
#counter_test.cpp
#darray_test.cpp
#div_operator_test.cpp
#index_iterator_test.cpp
#index_map_test.cpp
#iterator_test.cpp
#mult_operator_test.cpp
#numarray_test.cpp
#sarray_test.cpp
#scalar_test.cpp
#size_type_test.cpp
#slice_test.cpp
#static_cindex_map_test.cpp
#sub_operator_test.cpp
#value_ref_test.cpp
#value_test.cpp


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../src")
add_executable(pnicoretest ${TEST_SOURCES})
add_executable(rand_test "rand_test.cpp")
target_link_libraries(pnicoretest pnicore)
target_link_libraries(rand_test pnicore)

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

