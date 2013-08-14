
#gather all source files for the library
file(GLOB_RECURSE SOURCES *.cpp)

add_library(pniio SHARED ${SOURCES})
set_target_properties(pniio PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")

install(TARGETS pniio LIBRARY DESTINATION "lib")
install(DIRECTORY . DESTINATION "include/pni/core" 
    FILES_MATCHING PATTERN "*.hpp")
