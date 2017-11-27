set(HEADER_FILES arrays.hpp
                 benchmark.hpp
                 configuration.hpp
                 types.hpp
                 utilities.hpp
                 error.hpp
                 type_erasures.hpp
                 algorithms.hpp
                 windows.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#-----------------------------------------------------------------------------
# build all the components required to assemble the library
#-----------------------------------------------------------------------------
set(PNICORE_LIBRARY_SOURCES )
set(PNICORE_LIBRARY_HEADERS )
add_subdirectory(algorithms)
add_subdirectory(arrays)
add_subdirectory(benchmark)
add_subdirectory(configuration)
add_subdirectory(error)
add_subdirectory(type_erasures)
add_subdirectory(types)
add_subdirectory(utilities)


set(CMAKE_DEBUG_TARGET_PROPERTIES
    INCLUDE_DIRECTORIES)
    

#-----------------------------------------------------------------------------
# building the shared library
#-----------------------------------------------------------------------------
message(STATUS "Building shared libraries ...")
add_library(pnicore_shared SHARED ${PNICORE_LIBRARY_SOURCES}
	                              ${PNICORE_LIBRARY_HEADERS}) 

target_link_libraries(pnicore_shared INTERFACE Boost::program_options
                                               Boost::system)
target_compile_definitions(pnicore_shared PUBLIC BOOST_ALL_DYN_LINK)

                           
#set private and public include directories
target_include_directories(pnicore_shared 
    PRIVATE ${PROJECT_SOURCE_DIR}/src
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>    
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
    
#set the package and SO version of the library
set_target_properties(pnicore_shared PROPERTIES 
                      VERSION "${PROJECT_VERSION}"
                      SOVERSION "${SO_VERSION}"
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

export(EXPORT pnicore_targets
       FILE ${PROJECT_BINARY_DIR}/cmake/pnicore_targets.cmake)



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


