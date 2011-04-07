lib_LTLIBRARIES = libfastcgi-daemon2.la

libfastcgi_daemon2_la_SOURCES = component.cpp config.cpp cookie.cpp except.cpp \
	handler.cpp handlerset.cpp loader.cpp logger.cpp parser.cpp request.cpp \
	requestimpl.cpp stream.cpp util.cpp xml.cpp componentset.cpp \
	component_factory.cpp component_context.cpp data_buffer.cpp string_buffer.cpp \
	server.cpp request_thread_pool.cpp globals.cpp response_time_statistics.cpp

AM_CPPFLAGS = -I../include -I../config @xml_CFLAGS@
AM_CXXFLAGS = -pthread
AM_LDFLAGS = -lpthread -ldl -lfcgi -lfcgi++ -lssl @BOOST_THREAD_LDFLAGS@ @BOOST_REGEX_LDFLAGS@ @xml_LIBS@
