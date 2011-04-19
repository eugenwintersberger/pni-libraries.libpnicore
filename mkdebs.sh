#!/bin/bash

#script for building Debian packages from the build

#The following packages can be build
#libpniutils_0.1.deb - library binary
#libpniutils-dev_0.1.deb - header files
#libpniutils-doc_0.1.deb - documentation files
#libpnituils-dbg_0.1.deb - library binary with debuging information

#first we need some functions that create the control files for the 
#packages
function 