check_PROGRAMS = test

test_SOURCES = main.cpp test_request.cpp test_config.cpp

test_CPPFLAGS = -I../include -I../config @CPPUNIT_CFLAGS@
test_CXXFLAGS = -pthread

test_LDADD = ../library/libfastcgi-daemon2.la
test_LDFLAGS = -lpthread @CPPUNIT_LIBS@

noinst_DATA = multipart-test-rn.dat multipart-test-n.dat test.conf

TESTS = test
