#ifndef _FASTCGI_LOGGER_H_
#define _FASTCGI_LOGGER_H_

#include <cstdarg>
#include <boost/utility.hpp>

namespace fastcgi
{

class Logger : private boost::noncopyable
{
public:
	enum Level {
		DEBUG, INFO, ERROR, EMERGENCY
	};
	
public:
	Logger();
	virtual ~Logger();

	void exiting(const char *function);
	void entering(const char *function);

	Level getLevel() const;
	void setLevel(const Level level);

	static Level stringToLevel(const std::string &);
	static std::string levelToString(const Level);

	virtual void info(const char *format, ...);
	virtual void debug(const char *format, ...);
	virtual void error(const char *format, ...);
	virtual void emerg(const char *format, ...);

	virtual void log(const Level level, const char *format, va_list args) = 0;

protected:
	virtual void setLevelInternal(const Level level);
	virtual void rollOver();

private:
	Level level_;
};


class BulkLogger : public Logger {
public:
	BulkLogger();

protected:
	virtual void log(const Level level, const char *format, va_list args);
};

} // namespace fastcgi

#endif // _FASTCGI_LOGGER_H_
