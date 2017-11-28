
add_subdirectory(_images)


set(RSTFILES index.rst
             introduction.rst
             installation.rst
             using.rst
             types.rst
             arrays.rst
             type_erasures.rst
             configuration.rst
             benchmarks.rst
    )

foreach(SRC ${RSTFILES})
    configure_file(${SRC} ${SRC} COPYONLY)
endforeach()


add_sphinx_source(${RSTFILES})
