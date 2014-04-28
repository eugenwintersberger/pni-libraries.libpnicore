#build documentation
include(FindDoxygen)

#list of sources for the documentation
set(HDR_DIR ../include/pni/core)

if(DOXYGEN_FOUND)
    #assemble the Doxygen file and the mainpage file
    if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
        configure_file(Doxyfile.cmake ./doc/Doxyfile @ONLY)
        #ass
        configure_file(mainpage.cmake ./doc/mainpage @ONLY)
    else()
        configure_file(Doxyfile.cmake ./Doxyfile @ONLY)
        configure_file(mainpage.cmake mainpage @ONLY)
    endif()

    #--------------------------run doxygen------------------------------------
    add_custom_command(OUTPUT html COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile)
    add_custom_target(api_doc SOURCES "html")

    #------------------install the HTML documentation-------------------------
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
            DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")

    #------------------install the example files------------------------------
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples"
            DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")
else(DOXYGEN_FOUND)
    message("--- Disable building documentation")
endif(DOXYGEN_FOUND)
add_subdirectory(users_guide)

add_custom_target(doc DEPENDS api_doc users_guide)
