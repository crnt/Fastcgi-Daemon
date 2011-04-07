#ifndef _FASTCGI_DETAILS_GLOBALS_H_
#define _FASTCGI_DETAILS_GLOBALS_H_

#include <map>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace fastcgi
{

class ComponentSet;
class Config;
class HandlerSet;
class Loader;
class Logger;
class RequestsThreadPool;

class Globals : private boost::noncopyable {
public:
	Globals(Config *config);
	virtual ~Globals();

	Config* config() const;

	typedef std::map<std::string, boost::shared_ptr<RequestsThreadPool> > ThreadPoolMap;

	ComponentSet* components() const;
	HandlerSet* handlers() const;
	const ThreadPoolMap& pools() const;
	Loader* loader() const;
	Logger* logger() const;

	void stopThreadPools();
	void joinThreadPools();

private:
	void initPools();
	void initLogger();
	void startThreadPools();

private:
	ThreadPoolMap pools_;
	Config* config_;
	std::auto_ptr<Loader> loader_;
	std::auto_ptr<HandlerSet> handlerSet_;
	std::auto_ptr<ComponentSet> componentSet_;
	Logger* logger_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_GLOBALS_H_
