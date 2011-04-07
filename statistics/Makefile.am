pkglib_LTLIBRARIES = fastcgi2-statistics.la

fastcgi2_statistics_la_SOURCES = response_time_handler.cpp
fastcgi2_statistics_la_LIBADD = ../library/libfastcgi-daemon2.la
fastcgi2_statistics_la_LDFLAGS = -module -lpthread

AM_CPPFLAGS = -I../include -I../config
AM_CXXFLAGS = -pthread

noinst_HEADERS = response_time_handler.h