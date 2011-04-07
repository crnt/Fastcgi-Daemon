pkglib_LTLIBRARIES = fastcgi2-logger.la

fastcgi2_logger_la_SOURCES = logger.cpp
fastcgi2_logger_la_LIBADD = ../library/libfastcgi-daemon2.la
fastcgi2_logger_la_LDFLAGS = -module -lpthread -llog4cxx

AM_CPPFLAGS = -I../include -I../config
AM_CXXFLAGS = -pthread

noinst_HEADERS = logger.h
