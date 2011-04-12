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

#ifndef _FASTCGI_HANDLER_H_
#define _FASTCGI_HANDLER_H_

#include <boost/utility.hpp>
#include <boost/any.hpp>

#include <string>
#include <vector>
#include <map>

namespace fastcgi
{

class Request;

class HandlerContext {
public:
	virtual ~HandlerContext();

	virtual boost::any getParam(const std::string &name) const = 0;
	virtual void setParam(const std::string &name, const boost::any &value) = 0;
};

class Handler : private boost::noncopyable
{
public:
	Handler();
	virtual ~Handler();
	
	virtual void onThreadStart();
	virtual void handleRequest(Request *req, HandlerContext *context) = 0;
};

} // namespace fastcgi

#endif // _FASTCGI_HANDLER_H_
