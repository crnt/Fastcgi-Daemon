#ifndef _FASTCGI_DETAILS_HANDLERSET_H_
#define _FASTCGI_DETAILS_HANDLERSET_H_

#include <string>
#include <vector>
#include <map>
#include <set>

#include <boost/utility.hpp>
#include <boost/regex.hpp>

namespace fastcgi
{

class Config;
class ComponentSet;
class Handler;
class Request;

class HandlerSet : private boost::noncopyable
{
public:
	struct HandlerDescription {
		typedef std::map<std::string, boost::regex>  FilterMap;
		FilterMap filters;
		std::vector<Handler*> handlers;
		std::string poolName;
		std::string id;
	};
	typedef std::vector<HandlerDescription> HandlerArray;

public:
	HandlerSet();
	virtual ~HandlerSet();

	void init(const Config *config, const ComponentSet *componentSet);

	const HandlerSet::HandlerDescription* findURIHandler(const Request *request) const;
	void findPoolHandlers(const std::string &poolName, std::set<Handler*> &handlers) const;
	std::set<std::string> getPoolsNeeded() const;
	
private:
	HandlerArray handlers_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_HANDLERSET_H_
