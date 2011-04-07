#ifndef _FASTCGI_REQUEST_IO_STREAM_H_
#define _FASTCGI_REQUEST_IO_STREAM_H_

namespace fastcgi
{

class RequestIOStream {
public:
	virtual int read(char *buf, int size) = 0;
	virtual int write(const char *buf, int size) = 0;
	virtual void write(std::streambuf *buf) = 0;
};

} // namespace fastcgi

#endif // _FASTCGI_REQUEST_IO_STREAM_H_
