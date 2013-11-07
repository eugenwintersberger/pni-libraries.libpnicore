#build documentation
include(FindDoxygen)

#list of sources for the documentation
set(HEADER_FILES ../include/pni/core/array_view_selector.hpp
                 ../include/pni/core/value.hpp
                 ../include/pni/core/index_map/index_policy.hpp
                 ../include/pni/core/index_map/index_maps.hpp
                 ../include/pni/core/index_map/c_index_policy_imp.hpp
                 ../include/pni/core/index_map/index_map.hpp
                 ../include/pni/core/index_map/static_index_map.hpp
                 ../include/pni/core/index_map/index_map_common.hpp
                 ../include/pni/core/counter.hpp
                 ../include/pni/core/exception_utils.hpp
                 ../include/pni/core/numarray_tags.hpp
                 ../include/pni/core/id_type_map.hpp
                 ../include/pni/core/array_operations.hpp
                 ../include/pni/core/utilties.hpp
                 ../include/pni/core/array_holder_interface.hpp
                 ../include/pni/core/math/mt_inplace_arithmetics.hpp
                 ../include/pni/core/math/add.hpp
                 ../include/pni/core/math/inplace_arithmetics.hpp
                 ../include/pni/core/math/op_traits.hpp
                 ../include/pni/core/math/sub.hpp
                 ../include/pni/core/math/div_op.hpp
                 ../include/pni/core/math/mult.hpp
                 ../include/pni/core/exceptions.hpp
                 ../include/pni/core/types.hpp
                 ../include/pni/core/benchmark/benchmark_runner.hpp
                 ../include/pni/core/benchmark/chrono_timer.hpp
                 ../include/pni/core/benchmark/benchmark_result.hpp
                 ../include/pni/core/benchmark/clock_timer.hpp
                 ../include/pni/core/sarray.hpp
                 ../include/pni/core/container_iterator.hpp
                 ../include/pni/core/type_class_map.hpp
                 ../include/pni/core/index_iterator.hpp
                 ../include/pni/core/slice.hpp
                 ../include/pni/core/hardware/cpu.hpp
                 ../include/pni/core/hardware/cpuinfo.hpp
                 ../include/pni/core/scalar.hpp
                 ../include/pni/core/arrays.hpp
                 ../include/pni/core/array_iterator.hpp
                 ../include/pni/core/value_holder.hpp
                 ../include/pni/core/binary.hpp
                 ../include/pni/core/darray.hpp
                 ../include/pni/core/type_utils.hpp
                 ../include/pni/core/value_holder_interface.hpp
                 ../include/pni/core/array_selection.hpp
                 ../include/pni/core/range_distributor.hpp
                 ../include/pni/core/type_id_map.hpp
                 ../include/pni/core/config/cli_args.hpp
                 ../include/pni/core/config/library_config.hpp
                 ../include/pni/core/config/config_argument.hpp
                 ../include/pni/core/config/configuration.hpp
                 ../include/pni/core/config/config_parser.hpp
                 ../include/pni/core/config/config_option.hpp
                 ../include/pni/core/array.hpp
                 ../include/pni/core/array_holder.hpp
                 ../include/pni/core/numarray.hpp
                 ../include/pni/core/service.hpp
                 ../include/pni/core/array_view.hpp
                 ../include/pni/core/complex_utils.hpp
                 ../include/pni/core/type_info.hpp
                 ../include/pni/core/mdarray.hpp
                 ../include/pni/core/value_ref.hpp
                 ../include/pni/core/type_conversion.hpp
                 mainpage
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
