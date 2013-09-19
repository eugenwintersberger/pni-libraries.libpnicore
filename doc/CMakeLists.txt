#build documentation
include(FindDoxygen)

#assemble Doxygen File
if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    configure_file(Doxyfile.cmake ./doc/Doxyfile @ONLY)
else()
    configure_file(Doxyfile.cmake ./Doxyfile @ONLY)
endif()

#assemble the input file 
if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    configure_file(mainpage.cmake ./doc/mainpage @ONLY)
else()
    configure_file(mainpage.cmake mainpage @ONLY)
endif()

#run doxygen
add_custom_command(OUTPUT html COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile)
add_custom_target(documentation ALL SOURCES "html")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html" 
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples" 
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")

