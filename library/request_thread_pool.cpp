#include "settings.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

#include <fastcgi2/except.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/logger.h>

#include <fastcgi2/stream.h>

#include "details/handler_context.h"
#include "details/request_thread_pool.h"

namespace fastcgi
{

RequestsThreadPool::RequestsThreadPool(
	const unsigned threadsNumber, const unsigned queueLength, fastcgi::Logger *logger) :
		ThreadPool<RequestTask>(threadsNumber, queueLength), logger_(logger)
{}

RequestsThreadPool::~RequestsThreadPool()
{}

void
RequestsThreadPool::handleTask(RequestTask task) {
	try {
		try {
			std::auto_ptr<HandlerContext> context(new HandlerContextImpl);
			for (std::vector<Handler*>::iterator i = task.handlers.begin();
				 i != task.handlers.end();
				 ++i) {
				if (task.request->isProcessed()) {
					break;
				}
				(*i)->handleRequest(task.request.get(), context.get());
			}

			task.request->sendHeaders();
		}
		catch (const HttpException &e) {
			bool headersAlreadySent = false;
			try {
				task.request->setStatus(500);
			}
			catch (...) { // this means that headers already send and we cannot change status/headers and so on
				headersAlreadySent = true;
			}
			if (headersAlreadySent) {
				throw;
			}
			else {
				task.request->sendError(e.status());
			}
		}
		catch (const std::exception &e) {
			bool headersAlreadySent = false;
			try {
				task.request->setStatus(500);
			}
			catch (...) { // this means that headers already send and we cannot change status/headers and so on
				headersAlreadySent = true;
			}
			if (headersAlreadySent) {
				throw;
			}
			else {
				fastcgi::RequestStream stream(task.request.get());
				stream << e.what();
				task.request->sendError(500);
			}
		}
		catch (...) {
			bool headersAlreadySent = false;
			try {
				task.request->setStatus(500);
			}
			catch (...) { // this means that headers already send and we cannot change status/headers and so on
				headersAlreadySent = true;
			}
			if (headersAlreadySent) {
				throw;
			}
			else {
				fastcgi::RequestStream stream(task.request.get());
				stream << "fastcgi-daemon: got unknown exception from handler";
				task.request->sendError(500);
			}
		}
	}
	catch (const std::exception &e) {
		logger_->error("%s", e.what());
		throw;
	}
	catch (...) {
		logger_->error("RequestsThreadPool::handleTask: got unknown exception, it should't happen");
		throw;
	}
}

} // namespace fastcgi
