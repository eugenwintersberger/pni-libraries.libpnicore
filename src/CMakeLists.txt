
#setup configuration file
CONFIGURE_FILE(config.hpp.cmake config.hpp @ONLY)
install(FILES config.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/pni/core")

#gather all source files for the library
file(GLOB_RECURSE SOURCES *.cpp)

add_library(pnicore SHARED ${SOURCES})
add_dependencies(pnicore config.hpp)
set_target_properties(pnicore PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")
target_link_libraries(pnicore boost_program_options boost_system boost_regex)

#install code
install(TARGETS pnicore LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(DIRECTORY . DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/pni/core" 
    FILES_MATCHING PATTERN "*.hpp")

#have to create the pkg-config file
CONFIGURE_FILE(pnicore.pc.cmake pnicore.pc @ONLY)
install(FILES pnicore.pc DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
install(FILES pnicore.cfg DESTINATION "${CMAKE_INSTALL_SYSCONFDIR}/pnicore")


