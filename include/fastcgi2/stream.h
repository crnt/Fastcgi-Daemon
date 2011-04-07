#ifndef _FASTCGI_STREAM_H_
#define _FASTCGI_STREAM_H_

#include <string>
#include <sstream>
#include <boost/utility.hpp>

namespace fastcgi
{

class Request;

class RequestStream : private boost::noncopyable
{
public:
	RequestStream(Request *req);
	virtual ~RequestStream();
	
	RequestStream& operator << (std::ostream& (*f)(std::ostream &os)) {
		stream_ << f;
		return *this;
	}
	
	template<typename T> RequestStream& operator << (const T &value) {
		stream_ << value;
		return *this;
	}

private:
	Request *request_;
	std::stringstream stream_;
};

} // namespace fastcgi

#endif // _FASTCGI_STREAM_H_
