Summary: The Externalization Template Library
Name: xtl
%define version 1.4
Version: %{version}
Release: 1
Group: Development/Libraries
Source: xtl-%{version}.tar.gz
Copyright: LGPL
Buildroot: /tmp/xtl-root
BuildArch: noarch

%description
The XTL is a library of template classes and functions for
reading/writing structured data to/from an external (platform
independent) representation. This process is also usually known as
marshalling, serialization or pickling, and is useful both for
heterogeneous network programming and portable persistent storage.

%prep
%setup

%build
make -C doc

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/include/xtl
chmod 755 $RPM_BUILD_ROOT/usr/include/xtl
install -m 644 include/xtl/* $RPM_BUILD_ROOT/usr/include/xtl
install -m 644 include/xtl.h $RPM_BUILD_ROOT/usr/include/xtl.h

%clean
rm -rf $RPM_BUILD_ROOT

%files
/usr/include/xtl/
/usr/include/xtl.h
%doc README
%doc COPYING.LIB
%doc doc/xtlguide.ps
%doc doc/xtlguide.pdf
