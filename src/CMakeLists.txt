
#gather all source files for the library
file(GLOB SOURCES *.cpp)

add_library(pnicore SHARED ${SOURCES})
add_dependencies(pnicore config.hpp)
set_target_properties(pnicore PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")
target_link_libraries(pnicore boost_program_options boost_system boost_regex)
set(PNICORE_COMPILER_FLAGS "")
get_target_property(PNICORE_COMPILER_FLAGS pnicore COMPILE_DEFINITIONS ) 
message("${PNICORE_COMPILER_FLAGS}") 

#install code
install(TARGETS pnicore LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

#have to create the pkg-config file
if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    CONFIGURE_FILE(pnicore.pc.cmake ./src/pnicore.pc @ONLY)
else()
    CONFIGURE_FILE(pnicore.pc.cmake pnicore.pc @ONLY)
endif()


install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pnicore.pc" 
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
install(FILES "pnicore.cfg" 
        DESTINATION "${CMAKE_INSTALL_SYSCONFDIR}/pnicore")

