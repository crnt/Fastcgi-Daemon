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
