#ifndef _FASTCGI_DATA_BUFFER_H_
#define _FASTCGI_DATA_BUFFER_H_

#include <utility>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

namespace fastcgi
{

/**
 * Chunked storage with shared internal buffer
 */

class DataBufferImpl;

class DataBuffer {
public:
	static DataBuffer create(const char *data, boost::uint64_t size);
	static DataBuffer create(DataBufferImpl *impl);

	DataBuffer();
	DataBuffer(DataBuffer buffer, boost::uint64_t begin, boost::uint64_t end);

	char at(boost::uint64_t pos) const;
	bool isNil() const;
	bool empty() const;
	boost::uint64_t size() const;
	void resize(boost::uint64_t size);

	class SegmentIterator;
	friend class SegmentIterator;

	SegmentIterator begin() const;
	SegmentIterator end() const;

	DataBuffer trim() const;
	DataBuffer trimn(boost::uint64_t b, boost::uint64_t e) const;
	bool split(const std::string &delim, DataBuffer &first, DataBuffer &second) const;
	bool split(char delim, DataBuffer &first, DataBuffer &second) const;
	bool startsWith(const std::string &data) const;
	bool startsWithCI(const std::string &data) const;
	bool endsWith(const std::string &data) const;
	bool endsWithCI(const std::string &data) const;
	void toString(std::string &str) const;

	boost::uint64_t read(boost::uint64_t pos, char *data, boost::uint64_t len);
	boost::uint64_t write(boost::uint64_t pos, const char *data, boost::uint64_t len);

	boost::uint64_t beginIndex() const;
	boost::uint64_t endIndex() const;

	DataBufferImpl* impl() const;

private:
	void checkIndex(boost::uint64_t index) const;
	boost::uint64_t find(boost::uint64_t pos, const char* buf, boost::uint64_t len) const;

private:
	boost::shared_ptr<DataBufferImpl> data_;
	boost::uint64_t begin_;
	boost::uint64_t end_;
};

class DataBuffer::SegmentIterator {
public:
	SegmentIterator();
	std::pair<char*, boost::uint64_t> operator*() const;
	std::pair<char*, boost::uint64_t>* operator->() const;
	SegmentIterator& operator++();
	SegmentIterator operator++(int);
	SegmentIterator& operator--();
	SegmentIterator operator--(int);
private:
	friend class DataBuffer;
	friend bool operator==(const SegmentIterator &lhs, const SegmentIterator &rhs);
	friend bool operator!=(const SegmentIterator &lhs, const SegmentIterator &rhs);
	SegmentIterator(const DataBuffer &buffer); // begin iterator
	DataBufferImpl* impl() const;
private:
	DataBuffer buffer_;
	boost::uint64_t pos_begin_;
	boost::uint64_t pos_end_;
	mutable std::pair<char*, boost::uint64_t> data_;
};

bool operator==(const DataBuffer::SegmentIterator &lhs, const DataBuffer::SegmentIterator &rhs);
bool operator!=(const DataBuffer::SegmentIterator &lhs, const DataBuffer::SegmentIterator &rhs);

} // namespace fastcgi

#endif // _FASTCGI_DATA_BUFFER_H_
