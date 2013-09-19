
#setup configuration file
if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    CONFIGURE_FILE(./pni/core/config.hpp.cmake 
                   ./include/pni/core/config.hpp @ONLY)
else()
    CONFIGURE_FILE(./pni/core/config.hpp.cmake 
                   ./pni/core/config.hpp @ONLY)
endif()
   
#install the configuration header
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pni/core/config.hpp"
        DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core")

#install the header files
install(DIRECTORY . DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}" 
        FILES_MATCHING PATTERN "*.hpp")



