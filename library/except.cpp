#include "settings.h"

#include <cstdio>

#include "fastcgi2/except.h"
#include "details/parser.h"

#ifdef HAVE_LDMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

HttpException::HttpException(unsigned short status) :
	status_(status)
{
}

HttpException::~HttpException() throw () {
}

unsigned short
HttpException::status() const {
	return status_;
}

const char*
HttpException::what() const throw () {
	return Parser::statusToString(status_);
}

NotFound::NotFound() : HttpException(404)
{
}

BadMethod::BadMethod(const char *reason) : HttpException(400)
{
	snprintf(reason_, sizeof(reason_), "%s", reason);
}

const char*
BadMethod::reason() const {
	return reason_;
}

InternalError::InternalError() : HttpException(500)
{
}

} // namespace fastcgi
