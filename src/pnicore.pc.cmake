prefix = @CMAKE_INSTALL_PREFIX@
exec_prefix = ${prefix}
includedir = ${prefix}/include
libdir = ${prefix}/lib

Name: pnicore
Description: PNI core library
Version: @LIBRARY_VERSION@
Cflags: -I${includedir} @CMAKE_CXX_FLAGS@
Libs: -L${libdir} -lpnicore -lboost_program_options -lboost_regex -lboost_system
