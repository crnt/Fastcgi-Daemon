// Fastcgi Daemon - framework for design highload FastCGI applications on C++
// Copyright (C) 2011 Ilya Golubtsov <golubtsov@yandex-team.ru>

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

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
