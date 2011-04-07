pkglib_LTLIBRARIES = fastcgi2-filelogger.la

fastcgi2_filelogger_la_SOURCES = file_logger.cpp
fastcgi2_filelogger_la_LIBADD = ../library/libfastcgi-daemon2.la
fastcgi2_filelogger_la_LDFLAGS = -module -lpthread

AM_CPPFLAGS = -I../include -I../config
AM_CXXFLAGS = -pthread

noinst_HEADERS = file_logger.h