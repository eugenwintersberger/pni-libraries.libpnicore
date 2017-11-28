#build documentation
add_subdirectory(users_guide)
add_subdirectory(api_doc)
add_subdirectory(examples)

add_custom_target(html DEPENDS api_doc users_guide)


add_custom_target(install-html
    DEPENDS html
    COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_COMPONENT=doc_html
    -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake)


