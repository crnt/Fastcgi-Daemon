#ifndef _FASTCGI_DETAILS_LOADER_H_
#define _FASTCGI_DETAILS_LOADER_H_

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

#include <fastcgi2/component_factory.h>

namespace fastcgi
{

class Config;
class ComponentFactory;

class Loader : private boost::noncopyable
{
public:
	Loader();
	virtual ~Loader();

	virtual void init(const Config *config);
	virtual ComponentFactory *findComponentFactory(const std::string &type) const;
	
protected:
	virtual void load(const char *name, const char *path);
	void checkLoad(const char *err);

private:
	std::vector<void*> handles_;
	FactoryMap factories_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_LOADER_H_
