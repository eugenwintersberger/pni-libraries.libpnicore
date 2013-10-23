set(HEADER_FILES add.hpp 
                div_op.hpp 
                inplace_arithmetics.hpp 
                mt_inplace_arithmetics.hpp 
                mult.hpp 
                op_traits.hpp 
                sub.hpp)

install(FILES ${HEADER_FILES}
        DESTINATION  ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/math)
