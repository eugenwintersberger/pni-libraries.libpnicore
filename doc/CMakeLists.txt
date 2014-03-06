#build documentation
include(FindDoxygen)

#list of sources for the documentation
set(HDR_DIR ../include/pni/core)
set(HEADER_FILES 
                 ${HDR_DIR}/hardware/cpu.hpp
                 ${HDR_DIR}/hardware/cpuinfo.hpp
                 ${HDR_DIR}/arrays.hpp
                 
                 ${HDR_DIR}/error/exceptions.hpp
                 ${HDR_DIR}/error/exception_utils.hpp

                 ${HDR_DIR}/utilities/container_utils.hpp
                 ${HDR_DIR}/utilities/counter.hpp
                 ${HDR_DIR}/utilities/container_iterator.hpp
                 ${HDR_DIR}/utilities/service.hpp

                 ${HDR_DIR}/type_erasures/array_holder_interface.hpp
                 ${HDR_DIR}/type_erasures/value.hpp
                 ${HDR_DIR}/type_erasures/array_iterator.hpp
                 ${HDR_DIR}/type_erasures/value_holder.hpp
                 ${HDR_DIR}/type_erasures/value_holder_interface.hpp
                 ${HDR_DIR}/type_erasures/array.hpp
                 ${HDR_DIR}/type_erasures/array_holder.hpp
                 ${HDR_DIR}/type_erasures/value_ref.hpp
                 
                 ${HDR_DIR}/arrays/array_selection.hpp
                 ${HDR_DIR}/arrays/array_view.hpp
                 ${HDR_DIR}/arrays/mdarray.hpp
                 ${HDR_DIR}/arrays/scalar.hpp
                 ${HDR_DIR}/arrays/index_iterator.hpp
                 ${HDR_DIR}/arrays/slice.hpp
                 ${HDR_DIR}/arrays/math/add_op.hpp
                 ${HDR_DIR}/arrays/math/inplace_arithmetics.hpp
                 ${HDR_DIR}/arrays/math/op_traits.hpp
                 ${HDR_DIR}/arrays/math/sub_op.hpp
                 ${HDR_DIR}/arrays/math/div_op.hpp
                 ${HDR_DIR}/arrays/math/mult_op.hpp
                 ${HDR_DIR}/arrays/array_operations.hpp
                 ${HDR_DIR}/arrays/index_map/index_maps.hpp
                 ${HDR_DIR}/arrays/index_map/c_index_map_imp.hpp
                 ${HDR_DIR}/arrays/index_map/index_map.hpp
                 ${HDR_DIR}/arrays/index_map/static_index_map.hpp
                 ${HDR_DIR}/arrays/dimension_layout/dynamic_dim_layout.hpp
                 ${HDR_DIR}/arrays/dimension_layout/static_dim_layout.hpp
                 ${HDR_DIR}/arrays/dimension_layout/algorithms.hpp
                 ${HDR_DIR}/arrays/dimension_layout/dimension_layout.hpp
                 
                 ${HDR_DIR}/types/type_conversion.hpp
                 ${HDR_DIR}/types/id_type_map.hpp
                 ${HDR_DIR}/types/type_info.hpp
                 ${HDR_DIR}/types/complex_utils.hpp
                 ${HDR_DIR}/types/type_id_map.hpp
                 ${HDR_DIR}/types/binary.hpp
                 ${HDR_DIR}/types/type_utils.hpp
                 ${HDR_DIR}/types/type_class_map.hpp
                 ${HDR_DIR}/types/types.hpp
                 
                 ${HDR_DIR}/configuration/cli_args.hpp
                 ${HDR_DIR}/configuration/library_config.hpp
                 ${HDR_DIR}/configuration/config_argument.hpp
                 ${HDR_DIR}/configuration/configuration.hpp
                 ${HDR_DIR}/configuration/config_parser.hpp
                 ${HDR_DIR}/configuration/config_option.hpp
                 
                 ${HDR_DIR}/benchmark/benchmark_runner.hpp
                 ${HDR_DIR}/benchmark/chrono_timer.hpp
                 ${HDR_DIR}/benchmark/benchmark_result.hpp
                 ${HDR_DIR}/benchmark/clock_timer.hpp
                 mainpage.cmake
    )

if(DOXYGEN_FOUND)
    #assemble Doxygen File
    if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
        configure_file(Doxyfile.cmake ./doc/Doxyfile @ONLY)
    else()
        configure_file(Doxyfile.cmake ./Doxyfile @ONLY)
    endif()

    #assemble the input file
    if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
        configure_file(mainpage.cmake ./doc/mainpage @ONLY)
    else()
        configure_file(mainpage.cmake mainpage @ONLY)
    endif()

    #run doxygen
    add_custom_command(OUTPUT html COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
                       DEPENDS ${HEADER_FILES})
    add_custom_target(documentation ALL SOURCES "html")
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
            DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")

    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples"
            DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")
else(DOXYGEN_FOUND)
    message("--- Disable building documentation")
endif(DOXYGEN_FOUND)
