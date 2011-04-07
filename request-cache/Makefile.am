pkglib_LTLIBRARIES = fastcgi2-request-cache.la

fastcgi2_request_cache_la_SOURCES = file_cache.cpp file_buffer.cpp mmap_file.cpp
fastcgi2_request_cache_la_LIBADD = ../library/libfastcgi-daemon2.la
fastcgi2_request_cache_la_LDFLAGS = -module -lpthread

AM_CPPFLAGS = -I../include -I../config
AM_CXXFLAGS = -pthread

noinst_HEADERS = file_cache.h mmap_file.h file_buffer.h