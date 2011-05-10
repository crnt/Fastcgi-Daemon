#include "settings.h"

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "fcgi_server.h"
#include "fastcgi2/config.h"
#include "details/globals.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

fastcgi::FCGIServer *server;

void
signalHandler(int signo) {
	if ((SIGINT == signo || SIGTERM == signo) && ::server != NULL) {
		server->stop();
	}
}   

void
setUpSignalHandlers() {
	if (SIG_ERR == signal(SIGINT, signalHandler)) {
		throw std::runtime_error("Cannot set up SIGINT handler");
	} 
	if (SIG_ERR == signal(SIGTERM, signalHandler)) {
		throw std::runtime_error("Cannot set up SIGTERM handler");
	}
}

int
main(int argc, char *argv[]) {
	
	using namespace fastcgi;
	try {
	    std::auto_ptr<Config> config = Config::create(argc, argv);
	    boost::shared_ptr<Globals> globals(new Globals(config.get()));
		FCGIServer server(globals);
		::server = &server;
		setUpSignalHandlers();
		server.start();
		server.join();
		return EXIT_SUCCESS;
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
