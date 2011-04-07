#ifndef _FASTCGI_HANDLER_H_
#define _FASTCGI_HANDLER_H_

#include <boost/utility.hpp>
#include <boost/any.hpp>

#include <string>
#include <vector>
#include <map>

namespace fastcgi
{

class Request;

class HandlerContext {
public:
	virtual ~HandlerContext();

	virtual boost::any getParam(const std::string &name) const = 0;
	virtual void setParam(const std::string &name, const boost::any &value) = 0;
};

class Handler : private boost::noncopyable
{
public:
	Handler();
	virtual ~Handler();
	
	virtual void onThreadStart();
	virtual void handleRequest(Request *req, HandlerContext *context) = 0;
};

} // namespace fastcgi

#endif // _FASTCGI_HANDLER_H_
