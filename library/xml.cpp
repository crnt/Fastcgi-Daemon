#include "settings.h"

#include <stdexcept>
#include <libxml/xmlerror.h>

#include "details/xml.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

XmlUtils::XmlUtils() {

	xmlInitParser();
	
	xmlLoadExtDtdDefaultValue = 1;
	xmlSubstituteEntitiesDefault(0);
}

XmlUtils::~XmlUtils() {
	xmlCleanupParser();
}

void
XmlUtils::throwUnless(bool value) {
	if (!value) {
		const char *message = "unknown xml error";
		xmlErrorPtr err =xmlGetLastError();
		if (err && err->message) {
			message = err->message;
		}
		std::runtime_error exc(message);
		xmlResetLastError();
		throw exc;
	}
}

const char*
XmlUtils::value(xmlNodePtr node) {
	assert(node);
	xmlNodePtr child = node->children;
	if (child && xmlNodeIsText(child) && child->content) {
		return (const char*) child->content;
	}
	return NULL;
}

const char*
XmlUtils::value(xmlAttrPtr attr) {
	assert(attr);
	xmlNodePtr child = attr->children;
	if (child && xmlNodeIsText(child) && child->content) {
		return (const char*) child->content;
	}
	return NULL;
}

const char*
XmlUtils::attrValue(xmlNodePtr node, const char *name) {
	assert(node);
	xmlAttrPtr attr = xmlHasProp(node, (const xmlChar*) name);
	return attr ? value(attr) : NULL;
}

void
XmlDocCleaner::clean(xmlDocPtr doc) {
	xmlFreeDoc(doc);
}

void
XmlNodeCleaner::clean(xmlNodePtr node) {
	xmlFreeNode(node);
}

void
XmlXPathObjectCleaner::clean(xmlXPathObjectPtr obj) {
	xmlXPathFreeObject(obj);
}

void
XmlXPathContextCleaner::clean(xmlXPathContextPtr ctx) {
	xmlXPathFreeContext(ctx);
}

} // namespace fastcgi
