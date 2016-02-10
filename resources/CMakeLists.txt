set(RCFILES icon.png)

foreach(F ${RCFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()
