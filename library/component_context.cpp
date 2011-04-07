#include "settings.h"

#include "details/component_context.h"
#include "details/componentset.h"
#include "details/globals.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

ComponentContextImpl::ComponentContextImpl(
	const Globals *globals, const std::string &componentXPath) :
		globals_(globals), componentXPath_(componentXPath)
{}
	
ComponentContextImpl::~ComponentContextImpl() {
}

const Config*
ComponentContextImpl::getConfig() const {
    return globals_->config();
}

const Globals*
ComponentContextImpl::globals() const {
    return globals_;
}

std::string
ComponentContextImpl::getComponentXPath() const {
    return componentXPath_;
}

Component*
ComponentContextImpl::findComponentInternal(const std::string &name) const {
    return globals_->components()->find(name);
}

} // namespace fastcgi
