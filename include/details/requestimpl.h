#ifndef _FASTCGI_DETAILS_REQUESTIMPL_H_
#define _FASTCGI_DETAILS_REQUESTIMPL_H_

#include <set>
#include <map>
#include <iosfwd>
#include <functional>
#include <boost/cstdint.hpp>

#include "settings.h"

#if defined(HAVE_STLPORT_HASHMAP)
#include <hash_set>
#include <hash_map>
#elif defined(HAVE_EXT_HASH_MAP) || defined(HAVE_GNUCXX_HASHMAP)
#include <ext/hash_set>
#include <ext/hash_map>
#endif

#include "fastcgi2/util.h"
#include "fastcgi2/cookie.h"

#include "details/range.h"
#include "details/functors.h"

namespace fastcgi
{

class File
{
public:
	File(DataBuffer filename, DataBuffer type, DataBuffer content);
	File(const std::string &filename, const std::string &type, DataBuffer content);
	
	const std::string& type() const;
	const std::string& remoteName() const;
	
	DataBuffer data() const;
	
private:
	std::string name_, type_;
	DataBuffer data_;
};

#if defined(HAVE_GNUCXX_HASHMAP)

typedef __gnu_cxx::hash_map<std::string, std::string, StringCIHash> VarMap;
typedef __gnu_cxx::hash_map<std::string, std::string, StringCIHash, StringCIEqual> HeaderMap;

#elif defined(HAVE_EXT_HASH_MAP) || defined(HAVE_STLPORT_HASHMAP)

typedef std::hash_map<std::string, std::string, StringCIHash> VarMap;
typedef std::hash_map<std::string, std::string, StringCIHash, StringCIEqual> HeaderMap;

#else

typedef std::map<std::string, std::string> VarMap;
typedef std::map<std::string, std::string, StringCILess> HeaderMap;

#endif

class Logger;
class Request;
class RequestCache;
class RequestIOStream;

class RequestImpl : private boost::noncopyable {
public:
	RequestImpl(Logger *logger, RequestCache *cache);
	~RequestImpl();

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

	bool isProcessed() const;
	void markAsProcessed();
	void tryAgain(time_t delay);

	void parse(DataBuffer buffer);
	void serialize(DataBuffer &buffer);
	void saveToCache(Request *request);

	void reset();
	void sendHeaders();
	void attach(RequestIOStream *stream, char *env[]);
	
	unsigned short status() const;

private:
	friend class Parser;
	void sendHeadersInternal();

	boost::uint64_t serializeEnv(DataBuffer &buffer, boost::uint64_t add_size);
	boost::uint64_t serializeInt(DataBuffer &buffer, boost::uint64_t pos, boost::uint64_t val);
	boost::uint64_t serializeString(DataBuffer &buffer, boost::uint64_t pos, const std::string &val);
	boost::uint64_t serializeBuffer(DataBuffer &buffer, boost::uint64_t pos, const DataBuffer &src);
	boost::uint64_t serializeFiles(DataBuffer &buffer, boost::uint64_t pos);
	boost::uint64_t serializeArgs(DataBuffer &buffer, boost::uint64_t pos);

	boost::uint64_t parseInt(DataBuffer buffer, boost::uint64_t pos, boost::uint64_t &val);
	boost::uint64_t parseString(DataBuffer buffer, boost::uint64_t pos, std::string &val);
	boost::uint64_t parseHeaders(DataBuffer buffer, boost::uint64_t pos);
	boost::uint64_t parseCookies(DataBuffer buffer, boost::uint64_t pos);
	boost::uint64_t parseVars(DataBuffer buffer, boost::uint64_t pos);
	boost::uint64_t parseBody(DataBuffer buffer, boost::uint64_t pos);
	boost::uint64_t parseFiles(DataBuffer buffer, boost::uint64_t pos);
	boost::uint64_t parseArgs(DataBuffer buffer, boost::uint64_t pos);

	boost::uint64_t bodySerializedSize();
	boost::uint64_t filesSerializedSize();
	boost::uint64_t argsSerializedSize();

private:
	bool headers_sent_;
	unsigned short status_;
	bool processed_;
	time_t delay_;

	RequestIOStream* stream_;
	VarMap vars_, cookies_;
	DataBuffer body_;
	HeaderMap headers_, out_headers_;

	std::set<Cookie> out_cookies_;
	std::map<std::string, File> files_;
	std::vector<StringUtils::NamedValue> args_;

	Logger* logger_;
	RequestCache* cache_;
};

} // namespace xscript

#endif // _FASTCGI_DETAILS_REQUESTIMPL_H_
