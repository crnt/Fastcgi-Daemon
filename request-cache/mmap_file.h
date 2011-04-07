#ifndef _FASTCGI_REQUEST_CACHE_MMAP_FILE_H_
#define _FASTCGI_REQUEST_CACHE_MMAP_FILE_H_

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

namespace fastcgi
{

class FileDescriptor {
public:
	FileDescriptor(int fdes) : fdes_(fdes) {}
	~FileDescriptor() {
		if (-1 != fdes_) {
			close(fdes_);
		}
	}

	int value() const {
		return fdes_;
	}
private:
	int fdes_;
};

class MMapFile {
public:
	MMapFile(const char *name, boost::uint64_t window, bool is_read_only = false);
	virtual ~MMapFile();

	boost::uint64_t size() const;
	bool empty() const;
	void resize(boost::uint64_t newsize);

	char at(boost::uint64_t index);
	char* atRange(boost::uint64_t index, boost::uint64_t length);
	std::pair<char*, boost::uint64_t> atSegment(boost::uint64_t index);

	boost::uint64_t window() const;

	MMapFile* clone() const;

private:
	MMapFile();
	void checkWindow();
	void unmap();
	char* map_segment(boost::uint64_t segment);
	char* map_range(boost::uint64_t begin, boost::uint64_t end);
	void check_index(boost::uint64_t index) const;
	bool mapped(boost::uint64_t index) const;
	bool mapped(boost::uint64_t begin, boost::uint64_t end) const;
	std::string error(int error);

private:
	void *pointer_;
	boost::uint64_t size_;
	boost::shared_ptr<FileDescriptor> fdes_;
	bool is_read_only_;
	boost::uint64_t window_;
	boost::uint64_t segment_start_, segment_len_;
	int page_size_;
};

} // namespace fastcgi

#endif // _FASTCGI_REQUEST_CACHE_MMAP_FILE_H_
