#ifndef _FASTCGI_DETAILS_HANDLER_CONTEXT_H_
#define _FASTCGI_DETAILS_HANDLER_CONTEXT_H_

#include <fastcgi2/handler.h>

#include <map>

namespace fastcgi 
{

class HandlerContextImpl : public HandlerContext {
public:
	virtual boost::any getParam(const std::string &name) const;
	virtual void setParam(const std::string &name, const boost::any &value);

private:
	typedef std::map<std::string, boost::any> ParamsMapType;
	ParamsMapType params_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_HANDLER_CONTEXT_H_
