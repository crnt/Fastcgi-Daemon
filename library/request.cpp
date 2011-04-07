#include "settings.h"

#include <boost/current_function.hpp>

#include "fastcgi2/request.h"
#include "details/requestimpl.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

Request::Request(Logger *logger, RequestCache *cache) :
	impl_(new RequestImpl(logger, cache))
{}

Request::~Request() {
	impl_->saveToCache(this);
}

unsigned short
Request::getServerPort() const {
	return impl_->getServerPort();
}

const std::string&
Request::getHost() const {
	return impl_->getHost();
}

const std::string&
Request::getServerAddr() const {
	return impl_->getServerAddr();
}

const std::string&
Request::getPathInfo() const {
	return impl_->getPathInfo();
}

const std::string&
Request::getPathTranslated() const {
	return impl_->getPathTranslated();
}

const std::string&
Request::getScriptName() const {
	return impl_->getScriptName();
}

const std::string&
Request::getScriptFilename() const {
	return impl_->getScriptFilename();
}

const std::string&
Request::getDocumentRoot() const {
	return impl_->getDocumentRoot();
}

const std::string&
Request::getRemoteUser() const {
	return impl_->getRemoteUser();
}

const std::string&
Request::getRemoteAddr() const {
	return impl_->getRemoteAddr();
}

const std::string&
Request::getQueryString() const {
	return impl_->getQueryString();
}

const std::string&
Request::getRequestMethod() const {
	return impl_->getRequestMethod();
}

std::streamsize
Request::getContentLength() const {
	return impl_->getContentLength();
}

const std::string&
Request::getContentType() const {
	return impl_->getContentType();
}

unsigned int
Request::countArgs() const {
	return impl_->countArgs();
}

bool
Request::hasArg(const std::string &name) const {
	return impl_->hasArg(name);
}

const std::string&
Request::getArg(const std::string &name) const {
	return impl_->getArg(name);
}

void
Request::getArg(const std::string &name, std::vector<std::string> &v) const {
	impl_->getArg(name, v);
}

void
Request::argNames(std::vector<std::string> &v) const {
	impl_->argNames(v);
}

unsigned int
Request::countHeaders() const {
	return impl_->countHeaders();
}

bool
Request::hasHeader(const std::string &name) const {
	return impl_->hasHeader(name);
}

const std::string&
Request::getHeader(const std::string &name) const {
	return impl_->getHeader(name);
}

void
Request::headerNames(std::vector<std::string> &v) const {
	impl_->headerNames(v);
}

unsigned int
Request::countCookie() const {
	return impl_->countCookie();
}

bool
Request::hasCookie(const std::string &name) const {
	return impl_->hasCookie(name);
}

const std::string&
Request::getCookie(const std::string &name) const {
	return impl_->getCookie(name);
}

void
Request::cookieNames(std::vector<std::string> &v) const {
	impl_->cookieNames(v);
}

bool
Request::hasFile(const std::string &name) const {
	return impl_->hasFile(name);
}

void
Request::remoteFiles(std::vector<std::string> &v) const {
	impl_->remoteFiles(v);
}

const std::string&
Request::remoteFileName(const std::string &name) const {
	return impl_->remoteFileName(name);
}

const std::string&
Request::remoteFileType(const std::string &name) const {
	return impl_->remoteFileType(name);
}

DataBuffer
Request::remoteFile(const std::string &name) const {
	return impl_->remoteFile(name);
}

bool
Request::isSecure() const {
	return impl_->isSecure();
}

DataBuffer
Request::requestBody() const {
	return impl_->requestBody();
}

void
Request::setCookie(const Cookie &cookie) {
	impl_->setCookie(cookie);
}

void
Request::setStatus(unsigned short status) {
	impl_->setStatus(status);
}

void
Request::sendError(unsigned short status) {
	impl_->sendError(status);
}

void
Request::setHeader(const std::string &name, const std::string &value) {
	impl_->setHeader(name, value);
}

void
Request::write(std::streambuf *buf) {
	impl_->write(buf);
}

std::streamsize
Request::write(const char *buf, std::streamsize size) {
	return impl_->write(buf, size);
}

std::string
Request::outputHeader(const std::string &name) const {
	return impl_->outputHeader(name);
}

void
Request::reset() {
	impl_->reset();
}

void
Request::sendHeaders() {
	impl_->sendHeaders();
}

void
Request::attach(RequestIOStream *stream, char *env[]) {
	impl_->attach(stream, env);
}

bool
Request::isProcessed() const {
	return impl_->isProcessed();
}

void
Request::markAsProcessed() {
	impl_->markAsProcessed();
}

void
Request::tryAgain(time_t delay) {
	impl_->tryAgain(delay);
}

void
Request::parse(DataBuffer buffer) {
	impl_->parse(buffer);
}

void
Request::serialize(DataBuffer &buffer) {
	impl_->serialize(buffer);
}

void
Request::redirectBack() {
	redirectToPath(getHeader("Referer"));
}

void
Request::redirectToPath(const std::string &path) {
	setStatus(302);
	setHeader("Location", path);
}

void
Request::setContentType(const std::string &type) {
	setHeader("Content-type", type);
}

void
Request::setContentEncoding(const std::string &encoding) {
	setHeader("Content-encoding", encoding);
}

unsigned short
Request::status() const {
	return impl_->status();
}

} // namespace fastcgi
