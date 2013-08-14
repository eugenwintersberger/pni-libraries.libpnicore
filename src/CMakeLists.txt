
#gather all source files for the library
file(GLOB_RECURSE SOURCES *.cpp)

add_library(pniio SHARED ${SOURCES})
set_target_properties(pniio PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")
target_link_libraries(pniio boost_program_options boost_system boost_regex)

install(TARGETS pniio LIBRARY DESTINATION "lib")
install(DIRECTORY . DESTINATION "include/pni/core" 
    FILES_MATCHING PATTERN "*.hpp")

#have to create the pkg-config file
CONFIGURE_FILE(pnicore.pc.cmake pnicore.pc @ONLY)
