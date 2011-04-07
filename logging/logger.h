#ifndef _FASTCGI_LOG4CXX_LOGGER_H_
#define _FASTCGI_LOG4CXX_LOGGER_H_

#include <log4cxx/logger.h>
#include <log4cxx/rollingfileappender.h>

#include "fastcgi2/logger.h"
#include "fastcgi2/component.h"
#include "fastcgi2/handler.h"

namespace fastcgi
{

class DefaultLogger : virtual public Logger, virtual public Component, virtual public Handler
{
public:
	DefaultLogger(ComponentContext *context);
	virtual ~DefaultLogger();

	virtual void onLoad();
	virtual void onUnload();

	virtual void handleRequest(Request *request, HandlerContext *handlerContext);
	
protected:
	virtual void log(const Level level, const char *format, va_list args);
	virtual void setLevelInternal(const Level level);
	virtual void rollOver();

private:
	static log4cxx::LevelPtr toLog4cxxLevel(const Level level);

private:
	log4cxx::LoggerPtr logger_;
	log4cxx::helpers::ObjectPtrT<log4cxx::RollingFileAppender> appender_;
};

} // namespace fastcgi

#endif // _FASTCGI_LOG4CXX_LOGGER_H_
