#makefile for building debian packages
VERSION=0.0.1
SOVERSION=0
SCONS=scons
INSTPATH=debian/tmp/usr/lib

clean:
	$(SCONS) -c

all:
	$(SCONS) all

install:
	$(SCONS) PREFIX=/usr DESTDIR=$(DESTDIR) install
	#creating links for libraries
	cd $(INSTPATH) && mv libpniutils.so libpniutils.so.$(VERSION)
	cd $(INSTPATH) && ln -s libpniutils.so.$(VERSION) libpniutils.so
	doxygen	
	
