#build documentation
add_subdirectory(users_guide)
add_subdirectory(api_doc)
add_subdirectory(examples)


configure_file(conf.py.in conf.py @ONLY)
configure_file(index.rst index.rst COPYONLY)

add_custom_target(html DEPENDS api_doc users_guide)

add_custom_target(users_guide
                  COMMAND sphinx-build -bhtml . build/html
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  DEPENDS api_doc
                  SOURCES ${CMAKE_SPHINX_SOURCES})


add_custom_target(install-html
    DEPENDS html
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=doc_html
    -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake)


