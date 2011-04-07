#ifndef _FASTCGI_DETAILS_STRING_BUFFER_H_
#define _FASTCGI_DETAILS_STRING_BUFFER_H_

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "fastcgi2/data_buffer.h"
#include "details/data_buffer_impl.h"

namespace fastcgi
{

class StringBuffer : public DataBufferImpl {
public:
	StringBuffer(const char *data, boost::uint64_t size);
	virtual ~StringBuffer();
	virtual boost::uint64_t read(boost::uint64_t pos, char *data, boost::uint64_t len);
	virtual boost::uint64_t write(boost::uint64_t pos, const char *data, boost::uint64_t len);
	virtual char at(boost::uint64_t pos);
	virtual boost::uint64_t find(boost::uint64_t begin, boost::uint64_t end, const char* buf, boost::uint64_t len);
	virtual std::pair<boost::uint64_t, boost::uint64_t> trim(boost::uint64_t begin, boost::uint64_t end) const;
	virtual std::pair<char*, boost::uint64_t> chunk(boost::uint64_t pos) const;
	virtual std::pair<boost::uint64_t, boost::uint64_t> segment(boost::uint64_t pos) const;
	virtual boost::uint64_t size() const;
	virtual void resize(boost::uint64_t size);
	virtual const std::string& filename() const;
	virtual DataBufferImpl* getCopy() const;
private:
	boost::shared_ptr<std::vector<char> > data_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_STRING_BUFFER_H_
