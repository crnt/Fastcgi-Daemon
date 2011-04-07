pkglib_LTLIBRARIES = fastcgi2-syslog.la

fastcgi2_syslog_la_SOURCES = syslog-logger.cpp
fastcgi2_syslog_la_LIBADD = ../library/libfastcgi-daemon2.la
fastcgi2_syslog_la_LDFLAGS = -module -lpthread

AM_CPPFLAGS = -I../include -I../config
AM_CXXFLAGS = -pthread

noinst_HEADERS = syslog-logger.h