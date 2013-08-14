
#gather all source files for the library
file(GLOB_RECURSE SOURCES *.cpp)

add_library(pnicore SHARED ${SOURCES})
set_target_properties(pnicore PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")
target_link_libraries(pnicore boost_program_options boost_system boost_regex)

install(TARGETS pnicore LIBRARY DESTINATION "lib")
install(DIRECTORY . DESTINATION "include/pni/core" 
    FILES_MATCHING PATTERN "*.hpp")

#have to create the pkg-config file
CONFIGURE_FILE(pnicore.pc.cmake pnicore.pc @ONLY)
install(FILES pnicore.pc DESTINATION "lib/pkgconfig")
