set(RCFILES icon.ico banner.ico ui_dialog.ico)

foreach(F ${RCFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()
