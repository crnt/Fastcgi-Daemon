#ifndef _FASTCGI_REQUEST_H_
#define _FASTCGI_REQUEST_H_

#include <string>
#include <vector>
#include <memory>

#include <boost/utility.hpp>

#include <fastcgi2/data_buffer.h>

namespace fastcgi
{

class Cookie;
class Logger;
class RequestCache;
class RequestIOStream;
class RequestImpl;

class Request : private boost::noncopyable {
public:
	Request(Logger *logger, RequestCache *cache);
	~Request();
	
	unsigned short getServerPort() const;
	const std::string& getHost() const;
	const std::string& getServerAddr() const;

	const std::string& getPathInfo() const;
	const std::string& getPathTranslated() const;
	
	const std::string& getScriptName() const;
	const std::string& getScriptFilename() const;
	
	const std::string& getDocumentRoot() const;
	
	const std::string& getRemoteUser() const;
	const std::string& getRemoteAddr() const;
	const std::string& getQueryString() const;
	const std::string& getRequestMethod() const;
	
	std::streamsize getContentLength() const;
	const std::string& getContentType() const;
	
	unsigned int countArgs() const;
	bool hasArg(const std::string &name) const;
	const std::string& getArg(const std::string &name) const;
	void getArg(const std::string &name, std::vector<std::string> &v) const;
	void argNames(std::vector<std::string> &v) const;
	
	unsigned int countHeaders() const;
	bool hasHeader(const std::string &name) const;
	const std::string& getHeader(const std::string &name) const;
	void headerNames(std::vector<std::string> &v) const;
	
	unsigned int countCookie() const;
	bool hasCookie(const std::string &name) const;
	const std::string& getCookie(const std::string &name) const;
	void cookieNames(std::vector<std::string> &v) const;

	bool hasFile(const std::string &name) const;
	void remoteFiles(std::vector<std::string> &v) const;
	
	const std::string& remoteFileName(const std::string &name) const;
	const std::string& remoteFileType(const std::string &name) const;
	DataBuffer remoteFile(const std::string &name) const;

	bool isSecure() const;
	DataBuffer requestBody() const;
	
	void setCookie(const Cookie &cookie);
	void setStatus(unsigned short status);
	void sendError(unsigned short status);
	void setHeader(const std::string &name, const std::string &value);
	
	void write(std::streambuf *buf);
	std::streamsize write(const char *buf, std::streamsize size);
	std::string outputHeader(const std::string &name) const;
	
	void reset();
	void sendHeaders();
	void attach(RequestIOStream *stream, char *env[]);

	bool isProcessed() const;
	void markAsProcessed();

	void tryAgain(time_t delay);

	void redirectBack();
	void redirectToPath(const std::string &path);
	
	void setContentType(const std::string &type);
	void setContentEncoding(const std::string &encoding);

	void parse(DataBuffer buffer);
	void serialize(DataBuffer &buffer);

	unsigned short status() const;

private:
	std::auto_ptr<RequestImpl> impl_;
};

} // namespace fastcgi

#endif // _FASTCGI_REQUEST_H_

