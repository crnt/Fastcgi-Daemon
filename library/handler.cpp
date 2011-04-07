#include "settings.h"

#include "details/handler_context.h"
#include "details/handlerset.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

HandlerContext::~HandlerContext() {
}
	
boost::any HandlerContextImpl::getParam(const std::string &name) const {
	ParamsMapType::const_iterator itr = params_.find(name);
	if (itr != params_.end()) {
		return itr->second;
	}
	return boost::any();
}

void HandlerContextImpl::setParam(const std::string &name, const boost::any &value) {
	params_[name] = value;
}
	
Handler::Handler() {
}

Handler::~Handler() {
}

void
Handler::onThreadStart() {
}

} // namespace fastcgi
