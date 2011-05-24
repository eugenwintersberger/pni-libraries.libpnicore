#makefile for building debian packages
VERSION=0.0.1
SOVERSION=0
SCONS=scons

clean:
	$(SCONS) -c

all:
	$(SCONS) all

install:
	doxygen
	$(SCONS) PREFIX=/usr DESTDIR=$(DESTDIR) install
	doxygen	
