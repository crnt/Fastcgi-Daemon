#ifndef _FASTCGI_DETAILS_RESPONSE_TIME_STATISTICS_H_
#define _FASTCGI_DETAILS_RESPONSE_TIME_STATISTICS_H_

#include <string>

#include <boost/cstdint.hpp>

namespace fastcgi
{

class ResponseTimeStatistics {
public:
	ResponseTimeStatistics();
	virtual ~ResponseTimeStatistics();

	virtual void add(const std::string &handler, unsigned short status, boost::uint64_t time) = 0;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_RESPONSE_TIME_STATISTICS_H_
