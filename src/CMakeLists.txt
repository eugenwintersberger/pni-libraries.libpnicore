
#-----------------------------------------------------------------------------
# build all the components required to assemble the library
#-----------------------------------------------------------------------------
add_subdirectory(types)
add_subdirectory(benchmark)
add_subdirectory(arrays)
add_subdirectory(configuration)
add_subdirectory(type_erasures)
add_subdirectory(misc)

set(LIB_TARGETS) # list of libray targets which will be installed

#-----------------------------------------------------------------------------
# building the shared library
#-----------------------------------------------------------------------------
if(BUILD_SHARED_LIBRARIES)
    message(STATUS "Building shared libraries ...")
    add_library(pnicore_shared SHARED 
                               $<TARGET_OBJECTS:type_objects_shared>
                               $<TARGET_OBJECTS:benchmark_objects_shared>
                               $<TARGET_OBJECTS:array_objects_shared>
                               $<TARGET_OBJECTS:configuration_objects_shared>
                               $<TARGET_OBJECTS:type_erasure_objects_shared>
                               $<TARGET_OBJECTS:misc_objects_shared>) 

    target_link_libraries(pnicore_shared INTERFACE
                               ${Boost_PROGRAM_OPTIONS_SHARED_LIBRARY}
                               ${Boost_SYSTEM_SHARED_LIBRARY})
    #set the package and SO version of the library
    set_target_properties(pnicore_shared PROPERTIES 
                          VERSION "${PROJECT_VERSION}"
                          SOVERSION "${SO_VERSION}"
                          OUTPUT_NAME pnicore)
    list(APPEND LIB_TARGETS pnicore_shared)
endif(BUILD_SHARED_LIBRARIES)


#-----------------------------------------------------------------------------
# building the static library if requested by the user
#-----------------------------------------------------------------------------
if(BUILD_STATIC_LIBRARIES)
    message(STATUS "Building static libraries ...")
    if(CMAKE_SYSTEM_NAME MATCHES Windows)
        set(STATIC_LIBNAME pnicore_static)
    else()
        set(STATIC_LIBNAME pnicore)
    endif()
    add_library(pnicore_static STATIC 
                               $<TARGET_OBJECTS:type_objects_static>
                               $<TARGET_OBJECTS:benchmark_objects_static>
                               $<TARGET_OBJECTS:array_objects_static>
                               $<TARGET_OBJECTS:configuration_objects_static>
                               $<TARGET_OBJECTS:type_erasure_objects_static>
                               $<TARGET_OBJECTS:misc_objects_static>) 
    set_target_properties(pnicore_static PROPERTIES
                          OUTPUT_NAME ${STATIC_LIBNAME})
    list(APPEND LIB_TARGETS pnicore_static)
endif(BUILD_STATIC_LIBRARIES)



#-----------------------------------------------------------------------------
# do the installation - there is some extra work we have to do on 
# Windows. The Windows Installer does not support absolut installation 
# paths, which makes absolut sense as the prefix is choosen during 
# the installation.
#-----------------------------------------------------------------------------
#install the libraries - on Windows
install(TARGETS ${LIB_TARGETS}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT libraries)


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

