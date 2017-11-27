
add_subdirectory(_images)
configure_file(conf.py.in conf.py @ONLY)

set(RSTFILES index.rst
             introduction.rst
             installation.rst
             using.rst
             types.rst
             arrays.rst
             type_erasures.rst
             configuration.rst
    )

foreach(SRC ${RSTFILES})
    configure_file(${SRC} ${SRC} COPYONLY)
endforeach()


add_custom_target(users_guide
                  COMMAND sphinx-build -bhtml . build/html
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  SOURCES ${RSTFILES})
