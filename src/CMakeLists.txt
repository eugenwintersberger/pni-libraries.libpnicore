
#gather all source files for the library
file(GLOB_RECURSE SOURCES *.cpp)

add_library(pniio SHARED ${SOURCES})
