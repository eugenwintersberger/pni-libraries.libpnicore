set(RCFILES icon.ico banner.ico)

foreach(F ${RCFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()
