#ifndef _FASTCGI_DETAILS_SERVER_H_
#define _FASTCGI_DETAILS_SERVER_H_

#include <boost/noncopyable.hpp>

#include "details/handlerset.h"
#include "details/request_thread_pool.h"

namespace fastcgi
{

class Globals;

class Server : private boost::noncopyable {
public:
	Server();
	virtual ~Server();
	
protected:
	virtual void handleRequest(RequestTask task);
	virtual const Globals* globals() const = 0;
	virtual Logger* logger() const = 0;

	void handleRequestInternal(const HandlerSet::HandlerDescription* handler, RequestTask task);
	const HandlerSet::HandlerDescription* getHandler(RequestTask task) const;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_SERVER_H_
