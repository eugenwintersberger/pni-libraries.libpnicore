
#setup configuration file
CONFIGURE_FILE(./pni/core/config.hpp.cmake ./pni/core/config.hpp @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pni/core/config.hpp"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/pni/core")

install(DIRECTORY . DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" 
    FILES_MATCHING PATTERN "*.hpp")



