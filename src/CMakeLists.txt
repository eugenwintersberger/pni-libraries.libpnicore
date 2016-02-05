
#gather all source files for the library

if(CMAKE_HOST_UNIX)
    add_definitions(-fPIC)
endif()

add_subdirectory(types)
add_subdirectory(benchmark)
add_subdirectory(arrays)
add_subdirectory(configuration)
add_subdirectory(type_erasures)
add_subdirectory(misc)

#set up the library target
add_library(pnicore SHARED $<TARGET_OBJECTS:type_objects>
                           $<TARGET_OBJECTS:benchmark_objects>
                           $<TARGET_OBJECTS:array_objects>
                           $<TARGET_OBJECTS:configuration_objects>
                           $<TARGET_OBJECTS:type_erasure_objects>
                           $<TARGET_OBJECTS:misc_objects>) 

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    message(STATUS "Linking is done automatically!")
else()
    message(STATUS "Dynamic linking required with GCC")
target_link_libraries(pnicore
                           ${Boost_PROGRAM_OPTIONS_LIBRARY}
                           ${Boost_REGEX_LIBRARY})
endif()

#set the version and SO version of the library
set_target_properties(pnicore PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")


if(CMAKE_HOST_UNIX)
    install(TARGETS pnicore 
            LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
else()
    #install the libraries - on Windows
    install(TARGETS pnicore 
            LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
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

