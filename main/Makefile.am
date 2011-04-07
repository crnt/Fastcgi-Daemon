sbin_PROGRAMS = fastcgi-daemon2

fastcgi_daemon2_SOURCES = main.cpp fcgi_server.cpp endpoint.cpp fcgi_request.cpp
fastcgi_daemon2_LDADD = ../library/libfastcgi-daemon2.la

AM_CPPFLAGS = -I@top_srcdir@/include -I@top_srcdir@/config
AM_LDFLAGS = @BOOST_THREAD_LDFLAGS@

noinst_HEADERS = fcgi_server.h endpoint.h fcgi_request.h
dist_sysconf_DATA = fastcgi.conf.example
