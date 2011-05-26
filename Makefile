#makefile for building debian packages
VERSION=0.1
SOVERSION=0
SCONS=scons
INSTPATH=debian/tmp/usr/lib
INSTROOT=debian/tmp/usr
INSTDOC=$(INSTROOT)/share/doc/libpniutils0-doc
LIBNAME=libpniutils.so
LIBSONAME=$(LIBNAME).$(SOVERSION)
LIBVNAME=$(LIBSONAME).$(VERSION)

clean:
	$(SCONS) -c

all:
	$(SCONS) LIBSONAME=$(LIBSONAME) all

install:
	$(SCONS) LIBSONAME=$(LIBSONAME) PREFIX=/usr DESTDIR=$(DESTDIR) install
	#creating links for libraries
	cd $(INSTPATH) && chmod guo-x libpniutils.so
	cd $(INSTPATH) && chmod go-w libpniutils.so
	cd $(INSTPATH) && mv libpniutils.so libpniutils.so.$(SOVERSION).$(VERSION)
	cd $(INSTPATH) && ln -s libpniutils.so.$(SOVERSION).$(VERSION) libpniutils.so.$(SOVERSION)
	cd $(INSTPATH) && ln -s libpniutils.so.$(SOVERSION).$(VERSION) libpniutils.so
	
	#build the documentation
	doxygen	
	cd doc/api-doc/latex && make
	install -d $(INSTDOC)/API $(INSTDOC)/API/html 
	install doc/api-doc/latex/refman.pdf $(INSTDOC)/API
	cp -r doc/api-doc/html/* $(INSTDOC)/API/html
	#install doc/api-doc/html/search/* $(INSTDOC)/API/html/search
	
	
	
	
