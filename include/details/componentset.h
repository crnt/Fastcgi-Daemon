#ifndef _FASTCGI_DETAILS_COMPONENTSET_H_
#define _FASTCGI_DETAILS_COMPONENTSET_H_

#include <boost/utility.hpp>

#include <string>
#include <map>
#include <vector>

namespace fastcgi
{

class Globals;
class Loader;
class Component;
class ComponentContext;

class ComponentSet : private boost::noncopyable
{
protected:
	struct ComponentContainer {
		ComponentContainer();

		Component *component;
		ComponentContext *context;
		bool isLoadingStarted;
    };
    typedef std::map<std::string, ComponentContainer> ComponentMap;
	
public:
	ComponentSet();
	virtual ~ComponentSet();

	void init(const Globals *globals);

	
	Component* find(const std::string &name) const;

protected:
	void add(const std::string &name, const std::string &type, const std::string &componentXPath);

	void sendOnLoadToComponents();
	void sendOnUnloadToComponents();
	void sendOnLoad(const std::string &componentName, ComponentContainer &cont);
	bool isComponentLoaded(const std::string &componentName) const;

private:
	ComponentMap components_;
	std::vector<std::string> loadingStack_;
	const Globals *globals_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_COMPONENTSET_H_
