
#-----------------------------------------------------------------------------
# build all the components required to assemble the library
#-----------------------------------------------------------------------------
add_subdirectory(types)
add_subdirectory(benchmark)
add_subdirectory(arrays)
add_subdirectory(configuration)
add_subdirectory(type_erasures)
add_subdirectory(misc)

set(CMAKE_DEBUG_TARGET_PROPERTIES
    INCLUDE_DIRECTORIES)


#-----------------------------------------------------------------------------
# building the shared library
#-----------------------------------------------------------------------------
message(STATUS "Building shared libraries ...")
add_library(pnicore_shared SHARED
                           $<TARGET_OBJECTS:type_objects>
                           $<TARGET_OBJECTS:benchmark_objects>
                           $<TARGET_OBJECTS:array_objects>
                           $<TARGET_OBJECTS:configuration_objects>
                           $<TARGET_OBJECTS:type_erasure_objects>
                           $<TARGET_OBJECTS:misc_objects>)

target_link_libraries(pnicore_shared PUBLIC Boost::program_options Boost::system)

#set private and public include directories
target_include_directories(pnicore_shared
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#set the package and SO version of the library
set_target_properties(pnicore_shared PROPERTIES
                      VERSION "${PROJECT_VERSION}"
                      #SOVERSION "${pnicore_SO_VERSION}"
                      OUTPUT_NAME pnicore)



#-----------------------------------------------------------------------------
# do the installation - there is some extra work we have to do on
# Windows. The Windows Installer does not support absolut installation
# paths, which makes absolut sense as the prefix is choosen during
# the installation.
#-----------------------------------------------------------------------------
#install the libraries
install(TARGETS pnicore_shared
        EXPORT pnicore_targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT libraries)

install(EXPORT pnicore_targets
        DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
        COMPONENT development)




#-----------------------------------------------------------------------------
# On Unix and Linux systems we have to deply a pkg-config file for later
# use of the library.
#
# We do not need this on Windows.
#-----------------------------------------------------------------------------
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    #obtain the compiler flags used to build the target
    get_directory_property(PNICORE_CMP_FLAGS_LIST DIRECTORY
                           ${CMAKE_CURRENT_SOURCE_DIR} COMPILE_DEFINITIONS)

    #need to add a check here if the list is empty
    set(PNICORE_CMP_FLAGS "")
    foreach(FLAG ${PNICORE_CMP_FLAGS_LIST})
        set(PNICORE_CMP_FLAGS "${PNICORE_CMP_FLAGS} -D${FLAG}")
    endforeach()

    configure_file(pnicore.pc.cmake pnicore.pc @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pnicore.pc"
            DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig")
elseif(CMAKE_SYSTEM_NAME MATCHES Windows)
    # on the Windows platform we also install the cmake package
    # configuration file. This should make using the library easier
    # on Windows.

endif()
