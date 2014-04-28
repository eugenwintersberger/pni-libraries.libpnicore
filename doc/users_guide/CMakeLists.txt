#build documentation

#get all the sources for the documentation
set(PDFLATEX_COMPILER pdflatex)
set(BIBTEX_COMMAND bibtex)
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
            pics/pni-cpp-libraries.pdf
    )


add_custom_command(OUTPUT libpnicore_ug.pdf 
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpnicore_ug.tex
                   COMMAND ${BIBTEX_COMMAND} libpnicore_ug
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpnicore_ug.tex
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape libpnicore_ug.tex
                   DEPENDS ${SOURCES}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   )

               add_custom_target(users_guide  DEPENDS "libpnicore_ug.pdf" )

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/libpnicore_ug.pdf" 
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")

