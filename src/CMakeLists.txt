
#-----------------------------------------------------------------------------
# On UNIX systems we have to ensure that reallocatable code is built 
#-----------------------------------------------------------------------------
if(CMAKE_HOST_UNIX)
    add_definitions(-fPIC)
endif()

#-----------------------------------------------------------------------------
# build all the components required to assemble the library
#-----------------------------------------------------------------------------
add_subdirectory(types)
add_subdirectory(benchmark)
add_subdirectory(arrays)
add_subdirectory(configuration)
add_subdirectory(type_erasures)
add_subdirectory(misc)

#-----------------------------------------------------------------------------
# assemble the shared library - this will be built on Unix and Windows 
# platforms
#-----------------------------------------------------------------------------
add_library(pnicore SHARED $<TARGET_OBJECTS:type_objects>
                           $<TARGET_OBJECTS:benchmark_objects>
                           $<TARGET_OBJECTS:array_objects>
                           $<TARGET_OBJECTS:configuration_objects>
                           $<TARGET_OBJECTS:type_erasure_objects>
                           $<TARGET_OBJECTS:misc_objects>) 

#-----------------------------------------------------------------------------
# In the case of the GNU compiler we have to link with the BOOST 
# libraries. On Windows they are statically linked automatically. 
#-----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
target_link_libraries(pnicore
                           ${Boost_PROGRAM_OPTIONS_LIBRARY}
                           ${Boost_SYSTEM_LIBRARY})
endif()

#set the package and SO version of the library
set_target_properties(pnicore PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")

#-----------------------------------------------------------------------------
# on Windows we also build the static library
#-----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    add_library(pnicore_static STATIC 
                               $<TARGET_OBJECTS:type_objects>
                               $<TARGET_OBJECTS:benchmark_objects>
                               $<TARGET_OBJECTS:array_objects>
                               $<TARGET_OBJECTS:configuration_objects>
                               $<TARGET_OBJECTS:type_erasure_objects>
                               $<TARGET_OBJECTS:misc_objects>) 
endif()



#-----------------------------------------------------------------------------
# do the installation - there is some extra work we have to do on 
# Windows. The Windows Installer does not support absolut installation 
# paths, which makes absolut sense as the prefix is choosen during 
# the installation.
#-----------------------------------------------------------------------------
if(CMAKE_HOST_UNIX)
    install(TARGETS pnicore 
            LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
else()
    #install the libraries - on Windows
    install(TARGETS pnicore pnicore_static
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT libraries)
endif()


#-----------------------------------------------------------------------------
# On Unix and Linux systems we have to deply a pkg-config file for later 
# use of the library.
#
# We do not need this on Windows.
#-----------------------------------------------------------------------------
if(CMAKE_HOST_UNIX)
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
endif()

