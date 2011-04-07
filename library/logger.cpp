#include "settings.h"

#include <ctime>
#include <cstdarg>
#include <stdexcept>
#include <strings.h>

#include "fastcgi2/util.h"
#include "fastcgi2/config.h"
#include "fastcgi2/logger.h"
#include "fastcgi2/request.h"
#include "fastcgi2/stream.h"

#include <syslog.h>

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

Logger::Logger()
{
	level_ = DEBUG;
}

Logger::~Logger() {
}

/*
void
Logger::handleRequest(Request *request) {
    request->setContentType("text/plain");
    const std::string &action = request->getArg("action");
    if ("setlevel" == action) {
        const std::string &level = request->getArg("level");
        setLevel(stringToLevel(level));
        RequestStream(request) << "level " << level << "successfully set";
    } else if ("rollover" == action) {
        rollOver();
        RequestStream(request) << "rollover successful";
    } else {
        RequestStream(request) << "bad action";
    }
}
*/

void
Logger::exiting(const char *function) {
	debug("exiting %s\n", function);
}

void
Logger::entering(const char *function) {
	debug("entering %s\n", function);
}

void
Logger::info(const char *format, ...) {
	va_list args;
	va_start(args, format);
	log(INFO, format, args);
	va_end(args);
}

void
Logger::debug(const char *format, ...) {
	va_list args;
	va_start(args, format);
	log(DEBUG, format, args);
	va_end(args);
}

void
Logger::error(const char *format, ...) {
	va_list args;
	va_start(args, format);
	log(ERROR, format, args);
	va_end(args);
}

void
Logger::emerg(const char *format, ...) {
	va_list args;
	va_start(args, format);
	log(EMERGENCY, format, args);
	va_end(args);
}

Logger::Level Logger::getLevel() const {
	return level_;
}

void Logger::setLevel(const Logger::Level level) {
	setLevelInternal(level);
	level_ = level;
}

Logger::Level Logger::stringToLevel(const std::string &name) {
    if (strncasecmp(name.c_str(), "INFO", sizeof("INFO")) == 0) {
        return INFO;
    } else if (strncasecmp(name.c_str(), "DEBUG", sizeof("DEBUG")) == 0) {
        return DEBUG;
    } else if (strncasecmp(name.c_str(), "ERROR", sizeof("ERROR")) == 0) {
        return ERROR;
    } else if (strncasecmp(name.c_str(), "EMERG", sizeof("EMERG")) == 0) {
        return EMERGENCY;
    } else {
	    throw std::runtime_error("bad string to log level cast)");	
	}	
}

std::string Logger::levelToString(const Level level) {
	switch (level) {
	case INFO:
		return "INFO";
	case DEBUG:
		return "DEBUG";
	case ERROR:
		return "ERROR";
	case EMERGENCY:
		return "EMERG";
	default:
		throw std::runtime_error("bad log level to string cast");
	} 
}

void Logger::setLevelInternal(const Level level) {
}

void Logger::rollOver() {
}

/*
const char*
Logger::level() const {
	switch (setlogmask(0)) {
		case LOG_INFO: 
			return "INFO";
		case LOG_DEBUG: 
			return "DEBUG";
		case LOG_ERR: 
			return "ERROR";
		case LOG_EMERG: 
			return "EMERG";
		default: 
			throw std::runtime_error("bad level");
	}
}

void
Logger::level(const char* value) {
	setlogmask(findLevel(value));
}

Logger*
Logger::instance() {
	assert(NULL != helper_.get());
	return helper_.get();
}

unsigned int
Logger::findLevel(const char *name) const {
	if (strncasecmp(name, "INFO", sizeof("INFO")) == 0) {
		return LOG_INFO;
	}
	if (strncasecmp(name, "DEBUG", sizeof("DEBUG")) == 0) {
		return LOG_DEBUG;
	}
	if (strncasecmp(name, "ERROR", sizeof("ERROR")) == 0) {
		return LOG_ERR;
	}
	if (strncasecmp(name, "EMERG", sizeof("EMERG")) == 0) {
		return LOG_EMERG;
	}
	throw std::runtime_error("bad level");
}

void
Logger::log(int value, const char *format, va_list args) {
	vsyslog(value, format, args);
}

void
Logger::attachImpl(LoggerHelper helper) {
	helper_ = helper; 
}

LoggerRegisterer::LoggerRegisterer(LoggerHelper helper) {
	Logger::attachImpl(helper);
}

*/

BulkLogger::BulkLogger() {
}

void BulkLogger::log(Level level, const char *format, va_list args) {
}

} // namespace fastcgi
