#ifndef _FASTCGI_COMPONENT_FACTORY_H_
#define _FASTCGI_COMPONENT_FACTORY_H_

#include <string>
#include <map>

#include <boost/utility.hpp>

namespace fastcgi
{

class Component;
class ComponentFactory;
class ComponentContext;
	
typedef std::map<std::string, ComponentFactory*> FactoryMap;

class ComponentFactory : private boost::noncopyable
{
public:
	ComponentFactory();
	virtual ~ComponentFactory();
	virtual Component* createComponent(ComponentContext *context) = 0;
}; 

template<typename T>
class DefaultComponentFactory : public ComponentFactory {
public:
	virtual Component* createComponent(ComponentContext *context) {
		return new T(context);
	}
	
	virtual ~DefaultComponentFactory() {
	}
};

} // namespace fastcgi

typedef fastcgi::FactoryMap* (*FastcgiGetFactoryMapFunction)();

#define FCGIDAEMON_REGISTER_FACTORIES_BEGIN() \
	extern "C" const fastcgi::FactoryMap* getFactoryMap() { \
		static fastcgi::FactoryMap m;
			        
#define FCGIDAEMON_ADD_DEFAULT_FACTORY(name, Type) \
		m.insert(std::make_pair((name), new fastcgi::DefaultComponentFactory<Type>));

#define FCGIDAEMON_ADD_FACTORY(name, factory) \
		m.insert(std::make_pair((name), (factory)));

#define FCGIDAEMON_REGISTER_FACTORIES_END() \
	    return &m; \
	}

#endif //_FASTCGI_COMPONENT_FACTORY_H_

