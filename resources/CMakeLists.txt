set(RCFILES icon.ico banner.bmp ui_dialog.bmp)

foreach(F ${RCFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()
