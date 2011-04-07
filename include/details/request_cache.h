#ifndef _FASTCGI_DETAILS_REQUEST_CACHE_H_
#define _FASTCGI_DETAILS_REQUEST_CACHE_H_

#include <time.h>
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>

namespace fastcgi
{

class DataBuffer;
class Request;

class RequestCache : private boost::noncopyable {
public:
	RequestCache() {};
	virtual ~RequestCache() {};

	virtual DataBuffer create() = 0;
	virtual void save(Request *request, time_t delay) = 0;
	virtual boost::uint32_t minPostSize() const = 0;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_REQUEST_CACHE_H_
