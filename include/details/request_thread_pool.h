#ifndef _FASTCGI_DETAILS_REQUEST_THREAD_POOL_H_
#define _FASTCGI_DETAILS_REQUEST_THREAD_POOL_H_

#include <fastcgi2/request.h>
#include <fastcgi2/request_io_stream.h>

#include "details/response_time_statistics.h"
#include "details/thread_pool.h"

namespace fastcgi {

class Handler;
class Logger;

struct RequestTask {
	boost::shared_ptr<Request> request;
	std::vector<Handler*> handlers;
	boost::shared_ptr<RequestIOStream> request_stream;
};

class RequestsThreadPool : public ThreadPool<RequestTask> {
public:
	RequestsThreadPool(const unsigned threadsNumber, const unsigned queueLength,
		fastcgi::Logger *logger);
	virtual ~RequestsThreadPool();
	virtual void handleTask(RequestTask task);
private:
	fastcgi::Logger *logger_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_REQUEST_THREAD_POOL_H_
