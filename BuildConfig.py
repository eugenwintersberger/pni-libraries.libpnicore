#default build configuration - this holds general purpose 
#configurations for the build

VERSION="0.1.0" #library version - release version

SOVERSION="1"   #library SOVERSION (needed for debian and RPM packages) - should
                #be consistent for each release for all binary packages.
LIBNAME="pniutils" #name of the shared library


#contact to the maintainer
MAINTAINER="Eugen Wintersberger"
MAINTAINER_MAIL="eugen.wintersberger@desy.de"

#where the installation should go
PREFIX="/usr"
INCDIR=PREFIX+"/include/pni/utils"
LIBDIR=PREFIX+"/lib"
DOCDIR=PREFIX+"/share/doc/lib"+LIBNAME+SOVERSION+"-"+VERSION




