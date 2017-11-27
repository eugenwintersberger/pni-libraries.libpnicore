set(IMAGES pni-cpp-libraries.png
    )

foreach(IMAGE ${IMAGES})
    configure_file(${IMAGE} ${IMAGE} COPYONLY)
endforeach()
