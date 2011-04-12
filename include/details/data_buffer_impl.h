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

#ifndef _FASTCGI_DETAILS_DATA_BUFFER_IMPL_H_
#define _FASTCGI_DETAILS_DATA_BUFFER_IMPL_H_

#include <string>
#include <boost/cstdint.hpp>

namespace fastcgi
{

class DataBufferImpl {
public:
	virtual ~DataBufferImpl() {};
	virtual boost::uint64_t read(boost::uint64_t pos, char *data, boost::uint64_t len) = 0;
	virtual boost::uint64_t write(boost::uint64_t pos, const char *data, boost::uint64_t len) = 0;
	virtual char at(boost::uint64_t pos) = 0;
	virtual boost::uint64_t find(boost::uint64_t begin, boost::uint64_t end, const char* buf, boost::uint64_t len) = 0;
	virtual std::pair<boost::uint64_t, boost::uint64_t> trim(boost::uint64_t begin, boost::uint64_t end) const = 0;
	virtual std::pair<char*, boost::uint64_t> chunk(boost::uint64_t pos) const = 0;
	virtual std::pair<boost::uint64_t, boost::uint64_t> segment(boost::uint64_t pos) const = 0;
	virtual boost::uint64_t size() const = 0;
	virtual void resize(boost::uint64_t size) = 0;
	virtual const std::string& filename() const = 0;
	virtual DataBufferImpl* getCopy() const = 0;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_DATA_BUFFER_IMPL_H_
