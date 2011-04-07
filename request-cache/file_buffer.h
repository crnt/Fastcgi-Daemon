#ifndef _FASTCGI_REQUEST_CACHE_FILE_BUFFER_H_
#define _FASTCGI_REQUEST_CACHE_FILE_BUFFER_H_

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include "details/data_buffer_impl.h"
#include "mmap_file.h"

namespace fastcgi
{

struct FileHolder {
	std::string filename;
	FileHolder(const std::string &name) : filename(name) {}
	~FileHolder() {
		unlink(filename.c_str());
	}
};

class FileBuffer : public DataBufferImpl {
public:
	FileBuffer(const char *name, boost::uint64_t window);
	virtual ~FileBuffer();
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
	FileBuffer();
private:
	std::auto_ptr<MMapFile> file_;
	boost::shared_ptr<FileHolder> holder_;
	mutable boost::mutex mutex_;
	boost::uint64_t window_;
};

} // namespace fastcgi

#endif // _FASTCGI_REQUEST_CACHE_FILE_BUFFER_H_
