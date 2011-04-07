#ifndef _FASTCGI_COOKIE_H_
#define _FASTCGI_COOKIE_H_

#include <ctime>
#include <memory>
#include <string>

namespace fastcgi
{

class Cookie {
public:
	Cookie(const std::string &name, const std::string &value);
	Cookie(const Cookie &cookie);
	virtual ~Cookie();
	Cookie& operator=(const Cookie &cookie);
	bool operator < (const Cookie &cookie) const;
	
	const std::string& name() const;
	const std::string& value() const;
	
	bool secure() const;
	void secure(bool value);
	
	time_t expires() const;
	void expires(time_t value);

	void permanent(bool value);
	bool permanent() const;

	void httpOnly(bool value);
	bool httpOnly() const;

	const std::string& path() const;
	void path(const std::string &value);
	
	const std::string& domain() const;
	void domain(const std::string &value);

	std::string toString() const;

	void urlEncode(bool value);

private:
    class CookieData;
    std::auto_ptr<CookieData> data_;
};

} // namespace fastcgi

#endif // _FASTCGI_COOKIE_H_
