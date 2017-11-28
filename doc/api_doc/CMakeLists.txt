include(FindDoxygen)

if(DOXYGEN_FOUND)
    configure_file(Doxyfile.cmake ./Doxyfile @ONLY)
    configure_file(mainpage.dox.cmake mainpage.dox @ONLY)
    set_source_files_properties(Doxyfile mainpage.dox
	                            PROPERTIES GENERATED TRUE)

    #--------------------------run doxygen------------------------------------
    add_custom_command(OUTPUT doxygen.stamp
                       COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
                       COMMAND echo "timestamp" &> doxygen.stamp
                       DEPENDS  Doxyfile mainpage.dox
                     )
    add_custom_target(api_doc SOURCES doxygen.stamp)

    #------------------install the HTML documentation-------------------------
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
            DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}${LIBRARY_VERSION}-doc"
            OPTIONAL
            COMPONENT doc_html)


else(DOXYGEN_FOUND)
    message("--- Disable building documentation")
endif(DOXYGEN_FOUND)

set(RST_FILES index.rst
              type_api.rst
              exception_api.rst
              type_erasure_api.rst
              configuration_api.rst)
foreach(F ${RST_FILES})
	configure_file(${F} ${F} COPYONLY)
endforeach()

add_sphinx_source(${RST_FILES})
