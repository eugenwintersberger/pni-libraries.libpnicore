
#gather all source files for the library
set(SOURCES array.cpp
            array_selection.cpp
            benchmark_result.cpp
            benchmark_runner.cpp
            chrono_timer.cpp
            cli_args.cpp
            complex_utils.cpp
            config_parser.cpp
            configuration.cpp
            exceptions.cpp
            exception_utils.cpp
            library_config.cpp
            range_distributor.cpp
            service.cpp
            slice.cpp
            types.cpp
            type_utils.cpp
            value.cpp
            value_ref.cpp)


#set up the library target
add_library(pnicore SHARED ${SOURCES})
add_dependencies(pnicore config.hpp)
#set the version and SO version of the library
set_target_properties(pnicore PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")

#add BOOST libraries to the target if they have been found
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(pnicore ${Boost_LIBRARIES})
endif()


#obtain the compiler flags used to build the target
get_directory_property(PNICORE_CMP_FLAGS_LIST DIRECTORY 
                       ${CMAKE_CURRENT_SOURCE_DIR} COMPILE_DEFINITIONS) 

set(PNICORE_CMP_FLAGS "")
foreach(FLAG ${PNICORE_CMP_FLAGS_LIST})
    set(PNICORE_CMP_FLAGS "${PNICORE_CMP_FLAGS} -D${FLAG}")
endforeach()

#install the libraries
install(TARGETS pnicore LIBRARY DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}")

#have to create the pkg-config file
if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    CONFIGURE_FILE(pnicore.pc.cmake ./src/pnicore.pc @ONLY)
else()
    CONFIGURE_FILE(pnicore.pc.cmake pnicore.pc @ONLY)
endif()

#install the configuration and the pkg-config file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pnicore.pc" 
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig")
install(FILES "pnicore.cfg" 
        DESTINATION "${CMAKE_INSTALL_FULL_SYSCONFDIR}/pnicore")

