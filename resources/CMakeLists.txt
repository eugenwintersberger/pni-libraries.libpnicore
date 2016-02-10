set(RCFILES icon.ico banner.ico ui_dialog.bmp)

foreach(F ${RCFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()
