#build documentation

#get all the sources for the documentation
set(PDFLATEX_COMPILER pdflatex)
set(BIBTEX_COMMAND bibtex)
set(IMAGES pics/array_3d_aorder.pdf
           pics/array_3d_corder.pdf
           pics/array_3d_forder.pdf
           pics/array_3d.pdf
           pics/md_array_basic_structure.png
           pics/pni-cpp-libraries.pdf
           pics/record_reader_model.png
           pics/index_map_diagram.png
           pics/static_index_map_diagram.png
           )

set(SOURCES tex/appendix_multidim_arrays.tex
            tex/array_general_concepts.tex
            tex/arrays.tex
            tex/configuration.tex
            tex/installation.tex
            tex/introduction.tex
            tex/type_erasures.tex
            tex/types.tex
            tex/using.tex
    )

set(MASTER libpnicore_ug.tex)
set(BIBFILE libpnicore_ug.bib)

foreach(IMAGE  ${IMAGES})
    configure_file(${IMAGE} ${IMAGE} COPYONLY)
endforeach()

foreach(TEXFILE ${SOURCES})
    configure_file(${TEXFILE} ${TEXFILE} COPYONLY)
endforeach()

configure_file(${MASTER} ${MASTER} COPYONLY)
configure_file(${BIBFILE} ${BIBFILE} COPYONLY)

add_custom_command(OUTPUT libpnicore_ug.pdf 
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape ${MASTER}
                   COMMAND ${BIBTEX_COMMAND} libpnicore_ug
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape ${MASTER}
                   COMMAND ${PDFLATEX_COMPILER} -shell-escape ${MASTER}
                   DEPENDS ${SOURCES} ${MASTER} ${IMAGES}
                   )

add_custom_target(users_guide  DEPENDS "libpnicore_ug.pdf" )

install(FILES "libpnicore_ug.pdf" 
        DESTINATION "${CMAKE_INSTALL_FULL_DOCDIR}")

