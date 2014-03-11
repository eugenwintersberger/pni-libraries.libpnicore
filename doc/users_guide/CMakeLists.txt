#build documentation

#SET(PDFLATEX_COMPILER_FLAGS "-shell-escape"
#    CACHE STRING "Flags passed to pdflatex")
#include(UseLATEX.cmake)

#get all the sources for the documentation
set(PDFLATEX_COMPILER pdflatex)
set(SOURCES libpnicore_ug.tex
            tex/appendix_multidim_arrays.tex
            tex/array_general_concepts.tex
            tex/arrays.tex
            tex/types.tex
            pics/array_3d_aorder.pdf
            pics/array_3d_corder.pdf
            pics/array_3d_forder.pdf
            pics/array_3d.pdf
            pics/md_array_basic_structure.png
    )


#run doxygen
#file(COPY tex pics libpnicore_ug.tex DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(OUTPUT libpnicore_ug.pdf 
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpnicore_ug.tex
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpnicore_ug.tex
                   DEPENDS ${SOURCES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   )
#add_latex_document(libpnicore_ug.tex
#    INPUTS tex/arrays.tex tex/types.tex tex/array_general_concepts.tex 
#    tex/appendix_multidim_arrays.tex
#    pics/md_array_basic_structure.png
#    pics/array_3d.pdf
#    pics/array_3d_corder.pdf
#    pics/array_3d_forder.pdf
#    pics/array_3d_aorder.pdf
#    CONFIGURE libpnicore_ug.tex
#    USE_PDF
#    )
add_custom_target(users_guide ALL DEPENDS "libpnicore_ug.pdf" )

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/libpnicore_ug.pdf" 
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")

