#ifndef _FASTCGI_UTIL_H_
#define _FASTCGI_UTIL_H_

#include <string>
#include <vector>
#include <boost/utility.hpp>

#include <fastcgi2/data_buffer.h>

namespace fastcgi
{

class Range;

class StringUtils : private boost::noncopyable
{
public:
	static std::string urlencode(const Range &val);
	static std::string urlencode(const std::string &val);
	
	static std::string urldecode(const Range &val);
	static std::string urldecode(DataBuffer data);
	static std::string urldecode(const std::string &val);
	
	typedef std::pair<std::string, std::string> NamedValue;
	
	static void parse(const Range &range, std::vector<NamedValue> &v);
	static void parse(const std::string &str, std::vector<NamedValue> &v);
	static void parse(DataBuffer data, std::vector<NamedValue> &v);
	
	static const std::string EMPTY_STRING;

private:
	static void urldecode(const Range &range, std::string &result);

	StringUtils();
	virtual ~StringUtils();
};

class HttpDateUtils : private boost::noncopyable
{
public:
	static time_t parse(const char *value);
	static std::string format(time_t value);

private:
	HttpDateUtils();
	virtual ~HttpDateUtils();
};

class HashUtils {
public:
	static std::string hexMD5(const char *key, unsigned long len);
};

} // namespace fastcgi

#endif // _FASTCGI_UTIL_H_
