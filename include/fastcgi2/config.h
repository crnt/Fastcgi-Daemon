#ifndef _FASTCGI_CONFIG_H_
#define _FASTCGI_CONFIG_H_

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iosfwd>

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

namespace fastcgi
{

typedef std::ostream& (*HelpFunc)(std::ostream &stream);

class Config : private boost::noncopyable {
public:
	Config();
	virtual ~Config();
	
	virtual int asInt(const std::string &value) const = 0;
	virtual int asInt(const std::string &value, int defval) const = 0;
	
	virtual std::string asString(const std::string &value) const = 0;
	virtual std::string asString(const std::string &value, const std::string &defval) const = 0;
	
	virtual void subKeys(const std::string &value, std::vector<std::string> &v) const = 0;
	
	static std::auto_ptr<Config> create(const char *file);
	static std::auto_ptr<Config> create(int &argc, char *argv[], HelpFunc func = NULL);

private:
	Config(const Config &);
	Config& operator = (const Config &);
};

} // namespace fastcgi

#endif // _FASTCGI_CONFIG_H_
