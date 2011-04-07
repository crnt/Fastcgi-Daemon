#ifndef _FASTCGI_DETAILS_COMPONENT_CONTEXT_H_
#define _FASTCGI_DETAILS_COMPONENT_CONTEXT_H_

#include <fastcgi2/component.h>

#include <string>

namespace fastcgi 
{

class Config;
class Globals;
	
class ComponentContextImpl : public ComponentContext {
public:
	ComponentContextImpl(const Globals *globals, const std::string &componentXPath);
	virtual ~ComponentContextImpl();

    virtual const Config* getConfig() const;
    virtual std::string getComponentXPath() const;

    const Globals* globals() const;

protected:
	virtual Component* findComponentInternal(const std::string &name) const;

private:
    const Globals *globals_;
    std::string componentXPath_;
};

} //namespace fastcgi

#endif //_FASTCGI_DETAILS_COMPONENT_CONTEXT_H_
