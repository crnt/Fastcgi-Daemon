%define _builddir	.
%define _rpmdir		.
%define _sourcedir	.
%define _specdir	.
%define _srcrpmdir	. 

Summary:	fastcgi-daemon2 is an application server for FastCGI
Name:		fastcgi-daemon2
Version:	2.8
Release:	5%{?dist}

License:	Yandex License
Group:		System Environment/Libraries
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:	boost-devel
BuildRequires:	automake, autoconf, libtool
BuildRequires:	pkgconfig
BuildRequires:  libxml2-devel
BuildRequires:  fcgi-devel
BuildRequires:  cppunit-devel
BuildRequires:	autoconf-extra-archive

Requires:	%{name}-libs


%description
fastcgi-daemon is an application server for FastCGI
applications wtiteen in C++. This is the core package.


%package        libs
Summary:        Libs for %{name}
Group:          System Environment/Libraries

%description libs
Libs for %{name}


%package	libs-devel
Summary:	Development environment for %{name}-libs
Group:		System Environment/Libraries
Requires:	%{name}-libs = %{version}-%{release}

%description libs-devel
Development environment for %{name}-libs


%package        syslog
Summary:        Syslog for %{name}
Group:          System Environment/Libraries
Requires:       %{name} = %{version}-%{release}

%description    syslog
Syslog for %{name}


%package        init
Summary:        Init scripts packet for %{name}
Group:          System Environment/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       lighttpd

%description    init
Init scripts packet for fastcgi-daemon


%build
ACLOCAL="/usr/bin/aclocal -I /usr/share/autoconf-archive" ./autogen.sh
%configure --sysconfdir=/etc/fastcgi2 \
	--localstatedir=/var/log/fastcgi2 \
	--enable-cppunit

make release=1


%check
make check


%install
rm -rf %{buildroot}
make install DESTDIR=%{buildroot}

install -d %{buildroot}%{_bindir}
install -m 755 extra/fastcgistart2.sh %{buildroot}%{_bindir} 
install -d %{buildroot}%{_sysconfdir}/init.d
install -m 755 extra/fastcgi-daemon2 %{buildroot}%{_sysconfdir}/init.d


%clean
rm -rf %{buildroot}


%post init
AVAILABLE_DIR=/etc/fastcgi2/available                                                                                                       
LOG_DIR=/var/log/fastcgi2                                                                                                                   
RUN_DIR=/var/run/fastcgi2                                                                                                                   
POSTSTART_DIR=/etc/fastcgi2/poststart                                                                                                       
POSTSTOP_DIR=/etc/fastcgi2/poststop                                                                                                         
CHECK_DIR=/etc/fastcgi2/check                                                                                                               
                                                                                                                                           
USER=www-data                                                                                                                              
                                                                                                                                           
mkdir -p $AVAILABLE_DIR $LOG_DIR $RUN_DIR $POSTSTART_DIR $POSTSTOP_DIR $CHECK_DIR                                                          
                                                                                                                                           
chown $USER $LOG_DIR $RUN_DIR                                                                                                              
chgrp $USER $LOG_DIR $RUN_DIR                                                                                                              

/sbin/chkconfig --add fastcgi-daemon2
                                                                                                                                           
%postun init
AVAILABLE_DIR=/etc/fastcgi2/available
LOG_DIR=/var/log/fastcgi2
RUN_DIR=/var/run/fastcgi2
POSTSTART_DIR=/etc/fastcgi2/poststart
POSTSTOP_DIR=/etc/fastcgi2/poststop
CHECK_DIR=/etc/fastcgi2/check

rmdir $AVAILABLE_DIR $LOG_DIR $RUN_DIR $POSTSTART_DIR $POSTSTOP_DIR $CHECK_DIR  >/dev/null 2>&1

/sbin/chkconfig --del fastcgi-daemon2


%files
%defattr(-,root,root)
%{_sbindir}/fastcgi-daemon2
%{_sysconfdir}/fastcgi2/fastcgi.conf.example

%files libs
%defattr(-,root,root)
%{_libdir}/libfastcgi-daemon2.so.*
%{_libdir}/fastcgi2/example.so.*


%files libs-devel
%defattr(-,root,root)
%{_includedir}/*
%{_libdir}/fastcgi2/*.a
%{_libdir}/*.a
%{_libdir}/fastcgi2/*.la
%{_libdir}/*.la
%{_libdir}/fastcgi2/*.so
%{_libdir}/*.so


%files init
%defattr(-,root,root)
%{_bindir}/fastcgistart2.sh
%{_sysconfdir}/init.d/fastcgi-daemon2


%files syslog
%defattr(-,root,root)
%{_libdir}/fastcgi2/fastcgi2-syslog.so.*


%changelog
* Thu Oct 29 2009 Arkady L. Shane <ashejn@yandex-team.ru> 
- initial yandex's rpm build
