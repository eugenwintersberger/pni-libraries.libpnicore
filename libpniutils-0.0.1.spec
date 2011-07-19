Summary: utility library for PNI applications
Name: libpniutils
Version: 0.0.1
Release: 0
Copyright: GPL
Group: Development/Libraries
%description
This library provides classes and functions useful for developers
working for PNI facilities.

%build
scons all

%install
scons PREFIX=/usr install