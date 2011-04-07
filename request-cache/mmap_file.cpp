#include "settings.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <stdexcept>

#include "mmap_file.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

MMapFile::MMapFile() :
	pointer_(NULL), size_(0), fdes_(new FileDescriptor(-1)), is_read_only_(false),
	window_(0), segment_start_(0), segment_len_(0), page_size_(0)
{}

MMapFile::MMapFile(const char *name, boost::uint64_t window, bool is_read_only) :
	pointer_(NULL), size_(0), fdes_(new FileDescriptor(-1)), is_read_only_(is_read_only),
	window_(window), segment_start_(0), segment_len_(0), page_size_(getpagesize())
{
	if (is_read_only_) {
		fdes_.reset(new FileDescriptor(open(name, O_RDONLY)));
	}
	else {
		fdes_.reset(new FileDescriptor(open(name, O_RDWR | O_CREAT, 0644)));
	}

	if (-1 == fdes_->value()) {
		throw std::runtime_error(error(errno));
	}

	struct stat fs;
	if (-1 == fstat(fdes_->value(), &fs)) {
		throw std::runtime_error(error(errno));
	}

	size_ = fs.st_size;
	checkWindow();
	map_segment(0);
}

void
MMapFile::checkWindow() {
	if (0 == window_) {
		window_ = 10 * page_size_;
	}
	else {
		boost::uint64_t window_index = window_ / page_size_;
		boost::uint64_t offset = window_ - window_index * page_size_;
		if (0 != offset) {
			++window_index;
		}
		window_ = page_size_ * window_index;
	}
}

MMapFile*
MMapFile::clone() const {
	std::auto_ptr<MMapFile> file(new MMapFile);
	file->fdes_ = fdes_;
	file->size_ = size_;
	file->window_ = window_;
	file->page_size_ = page_size_;
	file->checkWindow();
	file->map_segment(0);
	return file.release();
}

MMapFile::~MMapFile() {
	if (fdes_.get() && -1 != fdes_->value()) {
		unmap();
	}
}

boost::uint64_t
MMapFile::size() const {
	return size_;
}

bool
MMapFile::empty() const {
	return 0 == size_;
}

std::string
MMapFile::error(int error) {
	char buffer[256];
	std::string result(strerror_r(error, buffer, sizeof(buffer)));
	return result;
}

void
MMapFile::resize(boost::uint64_t newsize) {
	unmap();
	if (-1 == ftruncate(fdes_->value(), newsize)) {
		throw std::runtime_error(error(errno));
	}
	size_ = newsize;
	map_segment(0);
}

char
MMapFile::at(boost::uint64_t index) {
	check_index(index);
	if (mapped(index)) {
		return *((char*)pointer_ + (index - segment_start_));
	}
	boost::uint64_t offset = index % window_, segment = index / window_;
	return *(map_segment(segment) + offset);
}

char*
MMapFile::atRange(boost::uint64_t index, boost::uint64_t length) {
	check_index(index);
	if (length > 0) {
		check_index(index + length - 1);
	}
	char* res = map_range(index, index + length);
	return res;
}

std::pair<char*, boost::uint64_t>
MMapFile::atSegment(boost::uint64_t index) {
	check_index(index);
	boost::uint64_t segment_pos = (index / window_) * window_;
	boost::uint64_t len = std::min(segment_pos + window_, size_) - index;
	char* segment = map_range(segment_pos, segment_pos + window_);
	return std::make_pair(segment + index - segment_pos, len);
}

void
MMapFile::unmap() {
	if (NULL != pointer_) {
		if (-1 == munmap(pointer_, segment_len_)) {
			throw std::runtime_error(error(errno));
		}
		pointer_ = NULL;
		segment_start_ = 0;
		segment_len_ = 0;
	}
}

char*
MMapFile::map_segment(boost::uint64_t segment) {
	boost::uint64_t pos = segment * window_;
	return map_range(pos, pos + window_);
}

char*
MMapFile::map_range(boost::uint64_t begin, boost::uint64_t end) {
	if (mapped(begin, end)) {
		return (char*)pointer_ + begin - segment_start_;
	}
	unmap();
	boost::uint64_t begin_base = page_size_ * (begin / page_size_);
	if (is_read_only_) {
		pointer_ = mmap(NULL, end - begin_base, PROT_READ, MAP_SHARED,
			fdes_->value(), begin_base);
	}
	else {
		pointer_ = mmap(NULL, end - begin_base, PROT_READ | PROT_WRITE, MAP_SHARED,
			fdes_->value(), begin_base);
	}
	if (MAP_FAILED == pointer_) {
		throw std::runtime_error(error(errno));
	}
	segment_start_ = begin_base;
	segment_len_ = end - begin_base;
	return (char*)pointer_ + (begin - begin_base);
}

void
MMapFile::check_index(boost::uint64_t index) const {
	if (index >= size_) {
		throw std::out_of_range("mapped file index out of range");
	}
}

boost::uint64_t
MMapFile::window() const {
	return window_;
}

bool
MMapFile::mapped(boost::uint64_t index) const {
	return mapped(index, index + 1);
}

bool
MMapFile::mapped(boost::uint64_t begin, boost::uint64_t end) const {
	return begin >= segment_start_ && end <= segment_start_ + segment_len_;
}

} // namespace fastcgi
