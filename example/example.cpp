#include "settings.h"

#include <iostream>
#include <stdexcept>

#include "fastcgi2/logger.h"
#include "fastcgi2/config.h"
#include "fastcgi2/stream.h"
#include "fastcgi2/handler.h"
#include "fastcgi2/request.h"
#include "fastcgi2/component.h"
#include "fastcgi2/component_factory.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace example
{

class ExampleHandler : virtual public fastcgi::Component, virtual public fastcgi::Handler
{
public:
	ExampleHandler(fastcgi::ComponentContext *context);
	virtual ~ExampleHandler();

	virtual void onLoad();
	virtual void onUnload();

	virtual void handleRequest(fastcgi::Request *req, fastcgi::HandlerContext *handlerContext);

private:
	fastcgi::Logger *logger_;
};

class ExampleHandler2 : virtual public fastcgi::Component, virtual public fastcgi::Handler
{
public:
    ExampleHandler2(fastcgi::ComponentContext *context);
    virtual ~ExampleHandler2();

    virtual void onLoad();
    virtual void onUnload();

    virtual void handleRequest(fastcgi::Request *req, fastcgi::HandlerContext *handlerContext);
};


ExampleHandler::ExampleHandler(fastcgi::ComponentContext *context) : fastcgi::Component(context), logger_(NULL) {
}

ExampleHandler::~ExampleHandler() {
}

void
ExampleHandler::onLoad() {	
	std::cout << "onLoad handler1 executed" << std::endl;
	const std::string loggerComponentName = context()->getConfig()->asString(context()->getComponentXPath() + "/logger");
	logger_ = context()->findComponent<fastcgi::Logger>(loggerComponentName);
	if (!logger_) {
		throw std::runtime_error("cannot get component " + loggerComponentName);
	}
}

void 
ExampleHandler::onUnload() {
	std::cout << "onUnload handler1 executed" << std::endl;
}

void
ExampleHandler::handleRequest(fastcgi::Request *req, fastcgi::HandlerContext *handlerContext) {

//	std::cout << req->countArgs() << ":" << req->getArg("a") << std::endl;
//	std::cout << "QUERY_STRING=" << req->getQueryString() << std::endl;

//	req->setContentType("text/plain");
	fastcgi::RequestStream stream(req);

/*	std::vector<std::string> names;
	req->argNames(names);
	for (std::vector<std::string>::iterator i = names.begin(), end = names.end(); i != end; ++i) {
		stream << "arg " << (*i) << " has value " << req->getArg(*i) << "\n";
	}
	req->headerNames(names);
	for (std::vector<std::string>::iterator i = names.begin(), end = names.end(); i != end; ++i) {
		stream << "header " << (*i) << " has value " << req->getHeader(*i) << "\n";
	}
	req->cookieNames(names);
	for (std::vector<std::string>::iterator i = names.begin(), end = names.end(); i != end; ++i) {
		stream << "cookie " << (*i) << " has value " << req->getCookie(*i) << "\n";
	}*/

	stream << "test ok\n";

//	logger_->info("request processed");

	req->setStatus(200);

//	handlerContext->setParam("param1", std::string("hi!"));
}

ExampleHandler2::ExampleHandler2(fastcgi::ComponentContext *context) : fastcgi::Component(context) {
}

ExampleHandler2::~ExampleHandler2() {
}

void
ExampleHandler2::onLoad() {  
	std::cout << "onLoad handler2 executed" << std::endl;
}

void
ExampleHandler2::onUnload() {
	std::cout << "onUnload handler2 executed" << std::endl;
}

void
ExampleHandler2::handleRequest(fastcgi::Request *req, fastcgi::HandlerContext *handlerContext) {
	boost::any param1 = handlerContext->getParam("param1");
	boost::any param2 = handlerContext->getParam("param2");

	if (param1.empty()) {
		std::cout << "param1 not found" << std::endl;
	} else {
		try {
			//std::cout << "value of param1 = " << boost::any_cast<std::string>(param1) << std::endl;
		} catch (const boost::bad_any_cast &) {
			//std::cout << "bad_any_cast: param1 is not string" << std::endl;
		}
	}

	if (param2.empty()) {
		//std::cout << "param2 not found" << std::endl;
	} else {
		//std::cout << "param1 found" << std::endl;
	}

	if (req->getScriptName() == "/upload" && req->getRequestMethod() == "POST") {
		fastcgi::DataBuffer f = req->remoteFile("file");
		std::string file;
		f.toString(file);
		//std::cout << "file=\n" << file << std::endl;
	}
}


FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("example", ExampleHandler)
FCGIDAEMON_ADD_DEFAULT_FACTORY("example2", ExampleHandler2)
FCGIDAEMON_REGISTER_FACTORIES_END()

} // namespace example
