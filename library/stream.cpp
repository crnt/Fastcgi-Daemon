#include "settings.h"
#include "fastcgi2/stream.h"
#include "fastcgi2/request.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

RequestStream::RequestStream(Request *req) :
	request_(req)
{
}

RequestStream::~RequestStream() {
	request_->write(stream_.rdbuf());
}

} // namespace fastcgi
