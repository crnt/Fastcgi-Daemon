#include "settings.h"

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include "details/handlerset.h"
#include "details/componentset.h"

#include "fastcgi2/config.h"
#include "fastcgi2/component.h"
#include "fastcgi2/handler.h"
#include "fastcgi2/request.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

HandlerSet::HandlerSet() {
}

HandlerSet::~HandlerSet() {
}

void
HandlerSet::init(const Config *config, const ComponentSet *componentSet) {
	std::vector<std::string> v;

    config->subKeys("/fastcgi/handlers/handler", v);
	for (std::vector<std::string>::const_iterator k = v.begin(), end = v.end(); k != end; ++k) {
		HandlerDescription handlerDesc;
		handlerDesc.poolName = config->asString(*k + "/@pool");
		handlerDesc.id = config->asString(*k + "/@id", "");

		const char *filterNames[] = {"url", "host", "address", "port"};
		for (unsigned i = 0; i < sizeof(filterNames) / sizeof(char*); ++i) {
			const std::string filterName = filterNames[i];
			const std::string filterValue = config->asString(*k + "/@" + filterName, "");
			if (!filterValue.empty()) {
				handlerDesc.filters.insert(std::make_pair(filterName, boost::regex(filterValue)));
			}
		}

		std::vector<std::string> components;
		config->subKeys(*k + "/component", components);
		for (std::vector<std::string>::const_iterator c = components.begin(); c != components.end(); ++c) {
			const std::string componentName = config->asString(*c + "/@name");
			Component *handlerComponent = componentSet->find(componentName);
			if (!handlerComponent) {
				throw std::runtime_error("Cannot find component: " + componentName);
			}
			
			Handler *handler = dynamic_cast<Handler*>(handlerComponent);
			if (!handler) {			
				throw std::runtime_error("Component " + componentName + " does not implement interface Handler");
			}
			
			handlerDesc.handlers.push_back(handler);
		}
		handlers_.push_back(handlerDesc);
	}
}

const HandlerSet::HandlerDescription*
HandlerSet::findURIHandler(const Request *request) const {
	for (HandlerArray::const_iterator i = handlers_.begin(); i != handlers_.end(); ++i) {
		bool matched = true;
		for (HandlerDescription::FilterMap::const_iterator f = i->filters.begin(); f != i->filters.end(); ++f) {
			if (f->first == "url" && !boost::regex_match(request->getScriptName(), f->second)) {
				matched = false;
				break;
			}
			else if (f->first == "host" && !boost::regex_match(request->getHost(), f->second)) {
				matched = false;
				break;
			}
			else if (f->first == "address" && !boost::regex_match(request->getServerAddr(), f->second)) {
				matched = false;
				break;
			}
			else if (f->first == "port" && !boost::regex_match(boost::lexical_cast<std::string>(request->getServerPort()), f->second)) {
				matched = false;
				break;
			}
		}

		if (matched) {
			return &(*i);
		}
    }
	return NULL;
}

void
HandlerSet::findPoolHandlers(const std::string &poolName, std::set<Handler*> &handlers) const {
	handlers.clear();
	for (HandlerArray::const_iterator it = handlers_.begin();
		 it != handlers_.end();
		 ++it) {
		if (it->poolName == poolName) {
			handlers.insert(it->handlers.begin(), it->handlers.end());
		}
	}
}

std::set<std::string>
HandlerSet::getPoolsNeeded() const {
	std::set<std::string> pools;
	for (HandlerArray::const_iterator i = handlers_.begin(); i != handlers_.end(); ++i) {
		pools.insert(i->poolName);
	}
	return pools;
}

} // namespace fastcgi

