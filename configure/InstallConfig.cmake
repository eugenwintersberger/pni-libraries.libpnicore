#check the installation configuration 

#====================for Linux systems==================================
# for systems with cmake >= 2.8 the GNUInstallDirs module provides all the
# installation paths. More precise this module defines all the variables
# required for the installation of the code. These variables are
#
# CMAKE_INSTALL_LIBDIR - path for library binaries 
# CMAKE_INSTALL_SYSCONFDIR - configuration direcotry (typically etc)
# CMAKE_INSTALL_DOCDIR - installation path for the documentation
# CMAKE_INSTALL_INCLUDEDIR - installation path for the header files
# 
# This module is particularly useful for Debian systems as it automatically
# determines the installation path for the libraries on multiarch systems.
#
# This module is not available on cmake 2.6 and thus we have to define this 
# variables manually
# 
if("${CMAKE_FAMILY_VERSION}" EQUAL "2.6")
    #most of the paths are canonic and thus easy to define
    set(CMAKE_INSTALL_SYSCONFDIR "${CMAKE_INSTALL_PREFIX}/etc")
    set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/share/doc")
    set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")

    #the library installation path is more difficult as we have several options
    #here
    # RedHat systems 32Bit: lib
    # RedHat systems 64Bit: lib64
    # Debian 32/64Bit     : lib
    # Debian multiarch    : lib/<ARCHSIG>
    #
    set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
else()
    include(GNUInstallDirs)
endif()

