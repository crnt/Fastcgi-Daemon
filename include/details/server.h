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

#ifndef _FASTCGI_DETAILS_SERVER_H_
#define _FASTCGI_DETAILS_SERVER_H_

#include <boost/noncopyable.hpp>

#include "details/handlerset.h"
#include "details/request_thread_pool.h"

namespace fastcgi
{

class Globals;

class Server : private boost::noncopyable {
public:
	Server();
	virtual ~Server();
	
protected:
	virtual void handleRequest(RequestTask task);
	virtual const Globals* globals() const = 0;
	virtual Logger* logger() const = 0;

	void handleRequestInternal(const HandlerSet::HandlerDescription* handler, RequestTask task);
	const HandlerSet::HandlerDescription* getHandler(RequestTask task) const;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_SERVER_H_
