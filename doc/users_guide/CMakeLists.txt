#build documentation

SET(LATEX_COMPILER_FLAGS "-shell-escape"
    CACHE STRING "Flags passed to latex")
SET(PDFLATEX_COMPILER_FLAGS "-shell-escape"
    CACHE STRING "Flags passed to pdflatex")
include(UseLATEX.cmake)

#run doxygen
#file(COPY tex pics libpnicore_ug.tex DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#add_custom_command(OUTPUT libpnicore_ug.pdf 
#                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpnicore_ug.tex
#                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpnicore_ug.tex
#                   DEPENDS "libpnicore_ug.tex")
add_latex_document(libpnicore_ug.tex
    INPUTS tex/arrays.tex tex/types.tex
    CONFIGURE libpnicore_ug.tex
    USE_PDF
    )
add_custom_target(users_guide ALL SOURCES "libpnicore_ug.pdf")

install(DIRECTORY users_guide
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")

