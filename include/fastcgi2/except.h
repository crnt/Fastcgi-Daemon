#ifndef _FASTCGI_EXCEPT_H_
#define _FASTCGI_EXCEPT_H_

#include <exception>

namespace fastcgi
{

class HttpException : public std::exception
{
public:
	HttpException(unsigned short status);
	virtual ~HttpException() throw ();
	
	unsigned short status() const;
	virtual const char* what() const throw ();

private:
	unsigned short status_;
};

class NotFound : public HttpException
{
public:
	NotFound();
};

class BadMethod : public HttpException
{
public:
	BadMethod(const char *reason);
	virtual const char* reason() const;
private:
	char reason_[256];
};

class InternalError : public HttpException
{
public:
	InternalError();
};

} // namespace fastcgi

#endif // _FASTCGI_EXCEPT_H_
