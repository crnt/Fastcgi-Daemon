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

#ifndef _FASTCGI_STREAM_H_
#define _FASTCGI_STREAM_H_

#include <string>
#include <sstream>
#include <boost/utility.hpp>

namespace fastcgi
{

class Request;

class RequestStream : private boost::noncopyable
{
public:
	RequestStream(Request *req);
	virtual ~RequestStream();
	
	RequestStream& operator << (std::ostream& (*f)(std::ostream &os)) {
		stream_ << f;
		return *this;
	}
	
	template<typename T> RequestStream& operator << (const T &value) {
		stream_ << value;
		return *this;
	}

private:
	Request *request_;
	std::stringstream stream_;
};

} // namespace fastcgi

#endif // _FASTCGI_STREAM_H_
