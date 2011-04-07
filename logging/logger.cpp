#include "settings.h"

#include <ctime>
#include <cstdio>
#include <cstdarg>
#include <stdexcept>

#include <log4cxx/patternlayout.h>

#include "fastcgi2/config.h"
#include "fastcgi2/logger.h"
#include "fastcgi2/component_factory.h"
#include "fastcgi2/request.h"
#include "fastcgi2/stream.h"
#include "logger.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

#if defined(HAVE_VA_COPY)
#define VA_COPY(a,b) va_copy((a), (b))
#elif defined(HAVE_NONSTANDARD_VA_COPY)
#define VA_COPY(a,b) __va_copy((a), (b))
#endif

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("logger", fastcgi::DefaultLogger)
FCGIDAEMON_REGISTER_FACTORIES_END()

namespace fastcgi
{

DefaultLogger::DefaultLogger(ComponentContext *context) 
	: Component(context), logger_(log4cxx::Logger::getRootLogger())
{
	const Config *config = context->getConfig();
	const std::string componentXPath = context->getComponentXPath();

	std::string layoutPattern = config->asString(componentXPath + "/pattern", "DEFAULT");

    log4cxx::LayoutPtr layout(new log4cxx::PatternLayout(
				"DEFAULT" == layoutPattern ? log4cxx::PatternLayout::TTCC_CONVERSION_PATTERN : layoutPattern));

    logger_ = log4cxx::Logger::getLogger(config->asString(componentXPath + "/ident"));

	const std::string logFileName = config->asString(componentXPath + "/file");
    appender_ = log4cxx::helpers::ObjectPtrT<log4cxx::RollingFileAppender>(new log4cxx::RollingFileAppender(layout, logFileName));

    appender_->setMaxFileSize("2000MB");

    logger_->addAppender(appender_);

    setLevel(stringToLevel(config->asString(componentXPath + "/level")));	
}

DefaultLogger::~DefaultLogger() {
}

void 
DefaultLogger::onLoad() {
}

void
DefaultLogger::onUnload() {
}

void
DefaultLogger::handleRequest(Request *request, HandlerContext *handlerContext) {
	request->setContentType("text/plain");
    const std::string &action = request->getArg("action");
    if ("setlevel" == action) {
        const std::string &l = request->getArg("level");
        setLevel(stringToLevel(l));
        RequestStream(request) << "level " << l << "successfully set" << std::endl;
    }
    else if ("rollover" == action) {
        rollOver();
        RequestStream(request) << "rollover successful" << std::endl;
    }
    else {
        RequestStream(request) << "bad action" << std::endl;
    }
}

void
DefaultLogger::rollOver() {
	appender_->rollOver();
}

void
DefaultLogger::setLevelInternal(const Level level) {
	logger_->setLevel(toLog4cxxLevel(level));
}

void
DefaultLogger::log(const Level level, const char *format, va_list args) {
	log4cxx::LevelPtr log4cxxLevel = toLog4cxxLevel(level);
	if (logger_->isEnabledFor(log4cxxLevel)) {
		va_list tmpargs;
		VA_COPY(tmpargs, args);
		size_t size = vsnprintf(NULL, 0, format, tmpargs);
		va_end(tmpargs);
		if (size > 0) {
			std::vector<char> data(size + 1);
			vsnprintf(&data[0], size + 1, format, args);
			logger_->log(log4cxxLevel, std::string(data.begin(), data.begin() + size));
		}
	}
}

log4cxx::LevelPtr
DefaultLogger::toLog4cxxLevel(const Level level) {
	switch (level) {
		case INFO:
			return log4cxx::Level::INFO;
		case DEBUG:
			return log4cxx::Level::DEBUG;
		case ERROR:
			return log4cxx::Level::ERROR;
		case EMERGENCY:
			return log4cxx::Level::FATAL;
		default:
			throw std::logic_error("toLog4cxxLevel: unknown log level");
	}
}

} // namespace fastcgi
