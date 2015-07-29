#build documentation
include(FindDoxygen)

#list of sources for the documentation
set(HDR_DIR ../include/pni/core)

if(DOXYGEN_FOUND)
    configure_file(Doxyfile.cmake ./Doxyfile @ONLY)
    configure_file(mainpage.cmake mainpage @ONLY)

    #--------------------------run doxygen------------------------------------
    add_custom_command(OUTPUT html COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile)
    add_custom_target(api_doc SOURCES "html")

    #------------------install the HTML documentation-------------------------
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
            DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc"
            OPTIONAL
            COMPONENT doc_html)


else(DOXYGEN_FOUND)
    message("--- Disable building documentation")
endif(DOXYGEN_FOUND)
add_subdirectory(users_guide)
add_subdirectory(examples)


add_custom_target(pdf DEPENDS users_guide)
add_custom_target(html DEPENDS api_doc)


add_custom_target(install-html
    DEPENDS html
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=doc_html
    -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake)

add_custom_target(install-pdf
    DEPENDS pdf
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=doc_pdf
    -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake)
