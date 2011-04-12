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

#ifndef _FASTCGI_DETAILS_PARSER_H_
#define _FASTCGI_DETAILS_PARSER_H_

#include <map>
#include <string>
#include <vector>
#include <iosfwd>
#include <boost/utility.hpp>

#include "settings.h"
#include "fastcgi2/util.h"
#include "details/range.h"
#include "details/functors.h"

namespace fastcgi
{

class File;
class Logger;
class RequestImpl;

class Parser : private boost::noncopyable {
public:
	static const char* statusToString(short status);
	static std::string getBoundary(const Range &range);
	
	static void addCookie(RequestImpl *req, const Range &range);
	static void addHeader(RequestImpl *req, const Range &key, const Range &value);

	static void parse(RequestImpl *req, char *env[], Logger* logger);
	static void parseCookies(RequestImpl *req, const Range &range);
	
	static void parsePart(RequestImpl *req, DataBuffer part);
	static void parseLine(DataBuffer line, DataBuffer &name, DataBuffer &filename, DataBuffer &type);
	static void parseMultipart(RequestImpl *req, DataBuffer data, const std::string &boundary);

	template<typename Map> static bool has(const Map &m, const std::string &key);
	template<typename Map> static void keys(const Map &m, std::vector<std::string> &v);
	template<typename Map> static const std::string& get(const Map &m, const std::string &key);

	static std::string normalizeInputHeaderName(const Range &range);
	static std::string normalizeOutputHeaderName(const std::string &name);

	static const Range RETURN_N_RANGE;
	static const Range RETURN_RN_RANGE;
	
	static const Range EMPTY_LINE_NN_RANGE;
	static const Range EMPTY_LINE_RNRN_RANGE;
	
	static const Range NAME_RANGE;
	static const Range FILENAME_RANGE;
	
	static const Range HEADER_RANGE;
	static const Range COOKIE_RANGE;
	static const Range CONTENT_TYPE_RANGE;
};

template<typename Map> inline bool
Parser::has(const Map &m, const std::string &key) {
	return m.find(key) != m.end();
}

template<typename Map> inline void
Parser::keys(const Map &m, std::vector<std::string> &v) {
	
	std::vector<std::string> tmp;
	tmp.reserve(m.size());
	
	for (typename Map::const_iterator i = m.begin(), end = m.end(); i != end; ++i) {
		tmp.push_back(i->first);
	}
	v.swap(tmp);
}

template<typename Map> inline const std::string&
Parser::get(const Map &m, const std::string &key) {
	typename Map::const_iterator i = m.find(key);
	return (m.end() == i) ? StringUtils::EMPTY_STRING : i->second;
}

} // namespace fastcgi

#endif //_FASTCGI_DETAILS_PARSER_H_
