
#setup configuration file
CONFIGURE_FILE(./pni/core/config.hpp.cmake ./pni/core/config.hpp @ONLY)


install(DIRECTORY . DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" 
    FILES_MATCHING PATTERN "*.hpp")



