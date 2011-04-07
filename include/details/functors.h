#ifndef _FASTCGI_DETAILS_FUNCTORS_H_
#define _FASTCGI_DETAILS_FUNCTORS_H_

#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <functional>
#include <boost/bind.hpp>
#include <boost/cstdint.hpp>

#include "settings.h"
#include "details/range.h"

namespace fastcgi
{

struct CharCILess : public std::binary_function<char, char, bool>
{
	bool operator () (char c, char target) const {
		return tolower(c) < tolower(target);
	}
};

struct RangeCILess : public std::binary_function<const Range&, const Range&, bool>
{
	bool operator() (const Range &range, const Range &target) const {
		return std::lexicographical_compare(range.begin(), range.end(), target.begin(), target.end(), CharCILess());
	}
};

#if defined(HAVE_GNUCXX_HASHMAP) || defined(HAVE_EXT_HASH_MAP) || defined(HAVE_STLPORT_HASHMAP)

struct StringCIHash : public std::unary_function<const std::string&, boost::uint32_t>
{
	boost::uint32_t operator () (const std::string &str) const {
		boost::uint32_t value = 0;
		for (std::string::const_iterator i = str.begin(), end = str.end(); i != end; ++i) {
			value += 5 * tolower(*i);
		}
		return value;
	}
};

struct StringCIEqual : public std::binary_function<const std::string&, const std::string&, bool>
{
	bool operator () (const std::string& str, const std::string& target) const {
		if (str.size() == target.size()) {
			return (strncasecmp(str.c_str(), target.c_str(), str.size()) == 0);
		}
		return false;
	}
};

#else

struct StringCILess : public std::binary_function<const std::string&, const std::string&, bool>
{
	bool operator () (const std::string& str, const std::string& target) const {
		return std::lexicagraphical_compare(str.begin(), str.end(), target.begin(), target.end(), CharCILess());
	}
};

#endif

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_FUNCTORS_H_
