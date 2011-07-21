%define name libpniutils
Name: %{name}
License: gpl
Summary: a testing package
%define version 0.0.1
Version: %{version}
%define release 0
Release: %{release}
Group: Development/Libraries
Source: http://nix.com
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}

%description
a more verbose description

%clean
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf "$RPM_BUILD_ROOT"

%prep
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf "$RPM_BUILD_ROOT"
%setup -q

%build
mkdir "$RPM_BUILD_ROOT"

%install
scons --install-sandbox="$RPM_BUILD_ROOT" "$RPM_BUILD_ROOT"

