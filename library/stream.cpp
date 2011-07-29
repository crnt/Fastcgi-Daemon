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
{}

RequestStream::~RequestStream() {
    if (stream_.rdbuf()->in_avail()) {
        request_->write(stream_.rdbuf());
    }
}

} // namespace fastcgi
