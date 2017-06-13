
#---------------------------------------------------------------------------------
# create and install the package version file
#---------------------------------------------------------------------------------
write_basic_package_version_file(
     ${PROJECT_BINARY_DIR}/${PACKAGE_VERSION_FILE_NAME}
     VERSION ${PROJECT_VERSION}
     COMPATIBILITY AnyNewerVersion)

install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_VERSION_FILE_NAME}
        DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
        COMPONENT development)

#----------------------------------------------------------------------------------
# create and install the package config file
#----------------------------------------------------------------------------------
configure_file(${PACKAGE_CONFIG_FILE_NAME} ${PACKAGE_CONFIG_FILE_NAME} COPYONLY)
install(FILES ${PROJECT_BINARY_DIR}/cmake/${PACKAGE_CONFIG_FILE_NAME}
        DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
        COMPONENT development)
