#include "settings.h"

#include <stdexcept>

#include "details/range.h"
#include "details/string_buffer.h"

#include "fastcgi2/util.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

StringBuffer::StringBuffer(const char *data, boost::uint64_t size) :
	data_(new std::vector<char>(data, data + size))
{}

StringBuffer::~StringBuffer()
{}

boost::uint64_t
StringBuffer::read(boost::uint64_t pos, char *data, boost::uint64_t len) {
	memcpy(data, &((*data_)[pos]), len);
	return len;
}

boost::uint64_t
StringBuffer::write(boost::uint64_t pos, const char *data, boost::uint64_t len) {
	memcpy(&((*data_)[pos]), data, len);
	return len;
}

char
StringBuffer::at(boost::uint64_t pos) {
	return data_->at(pos);
}

boost::uint64_t
StringBuffer::find(boost::uint64_t begin, boost::uint64_t end, const char* buf, boost::uint64_t len) {
	if (len > end - begin) {
		return end;
	}
	char* first = &((*data_)[0]);
	Range base(first + begin, first + end);
	Range substr(buf, buf + len);
	return base.find(substr) - first;
}

std::pair<boost::uint64_t, boost::uint64_t>
StringBuffer::trim(boost::uint64_t begin, boost::uint64_t end) const {
	char* first = &((*data_)[0]);
	Range base(first + begin, first + end);
	Range trimmed = base.trim();
	return std::pair<boost::uint64_t, boost::uint64_t>(
		trimmed.begin() - first, trimmed.end() - first);
}

std::pair<char*, boost::uint64_t>
StringBuffer::chunk(boost::uint64_t pos) const {
	return std::pair<char*, boost::uint64_t>(&((*data_)[0]) + pos, data_->size() - pos);
}

std::pair<boost::uint64_t, boost::uint64_t>
StringBuffer::segment(boost::uint64_t pos) const {
	return std::pair<boost::uint64_t, boost::uint64_t>(pos, size());
}

boost::uint64_t
StringBuffer::size() const {
	return data_->size();
}

void
StringBuffer::resize(boost::uint64_t size) {
	data_->resize(size);
}

const std::string&
StringBuffer::filename() const {
	return StringUtils::EMPTY_STRING;
}

DataBufferImpl*
StringBuffer::getCopy() const {
	return new StringBuffer(*this);
}

} // namespace fastcgi
