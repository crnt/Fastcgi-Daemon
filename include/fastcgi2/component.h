#ifndef _FASTCGI_COMPONENT_H_
#define _FASTCGI_COMPONENT_H_

#include <string>
#include <boost/utility.hpp>

namespace fastcgi
{

class Config;
class Component;

class ComponentContext : private boost::noncopyable
{
public:
	virtual ~ComponentContext();
	
	virtual const Config* getConfig() const = 0;
	virtual std::string getComponentXPath() const = 0;

	template<typename T>
	T* findComponent(const std::string &name) {
		return dynamic_cast<T*>(findComponentInternal(name));
	}

protected:	
	virtual Component* findComponentInternal(const std::string &name) const = 0;
};

class Component : private boost::noncopyable
{
public:
	Component(ComponentContext *context);
	virtual ~Component();

	virtual void onLoad() = 0;
	virtual void onUnload() = 0;

protected:
	ComponentContext* context();
	const ComponentContext* context() const;

private:
	ComponentContext *context_;
};

} // namespace fastcgi

#endif // _FASTCGI_COMPONENT_H_
