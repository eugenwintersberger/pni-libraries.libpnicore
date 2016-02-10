set(RCFILES icon.ico)

foreach(F ${RCFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()
