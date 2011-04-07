#ifndef _FASTCGI_DETAILS_XML_CONFIG_H_
#define _FASTCGI_DETAILS_XML_CONFIG_H_

#include "details/xml.h"

#include <fastcgi2/config.h>
#include <fastcgi2/helpers.h>

#include <libxml/tree.h>

#include <boost/regex.hpp>

#include <map>

namespace fastcgi
{

class XmlConfig : public Config
{
public:
	XmlConfig(const char *file);
	virtual ~XmlConfig();

	virtual int asInt(const std::string &value) const;
	virtual int asInt(const std::string &value, int defval) const;
	
	virtual std::string asString(const std::string &value) const;
	virtual std::string asString(const std::string &value, const std::string &defval) const;

	virtual void subKeys(const std::string &value, std::vector<std::string> &v) const;

private:
	XmlConfig(const XmlConfig &);
	XmlConfig& operator = (const XmlConfig &);
	
	void findVariables(const XmlDocHelper &doc);
	void resolveVariables(std::string &val) const;
	const std::string& findVariable(const std::string &key) const;
	
private:
	XmlDocHelper doc_;
	boost::regex regex_;
	std::map<std::string, std::string> vars_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_XML_CONFIG_H_
