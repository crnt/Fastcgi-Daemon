// Fastcgi Daemon - framework for design highload FastCGI applications on C++
// Copyright (C) 2011 Ilya Golubtsov <golubtsov@yandex-team.ru>

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

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
