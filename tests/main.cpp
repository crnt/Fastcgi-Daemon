#include "settings.h"

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include <cstdlib>

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

int
main(int argc, char *argv[]) {
	
	CppUnit::TextUi::TestRunner r;
	r.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
	return r.run("", false) ? EXIT_SUCCESS : EXIT_FAILURE;
}
