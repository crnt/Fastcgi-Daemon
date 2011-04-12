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

#ifndef _FASTCGI_DETAILS_XML_H_
#define _FASTCGI_DETAILS_XML_H_

#include <libxml/tree.h>
#include <libxml/xpath.h>

#include <boost/utility.hpp>
#include <fastcgi2/helpers.h>

namespace fastcgi
{

class XmlUtils : private boost::noncopyable
{
public:
	XmlUtils();
	virtual ~XmlUtils();
	
	static void throwUnless(bool value);
	static const char* value(xmlAttrPtr node);
	static const char* value(xmlNodePtr node);
	static const char* attrValue(xmlNodePtr node, const char *name);
};

struct XmlDocCleaner
{
	static void clean(xmlDocPtr doc);
};

struct XmlNodeCleaner
{
	static void clean(xmlNodePtr node);
};

struct XmlXPathObjectCleaner
{
	static void clean(xmlXPathObjectPtr obj);
};

struct XmlXPathContextCleaner
{
	static void clean(xmlXPathContextPtr ctx);
};

typedef Helper<xmlDocPtr, XmlDocCleaner> XmlDocHelper;
typedef Helper<xmlNodePtr, XmlNodeCleaner> XmlNodeHelper;
typedef Helper<xmlXPathObjectPtr, XmlXPathObjectCleaner> XmlXPathObjectHelper;
typedef Helper<xmlXPathContextPtr, XmlXPathContextCleaner> XmlXPathContextHelper;

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_XML_H_
