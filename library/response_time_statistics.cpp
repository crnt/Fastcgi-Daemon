#include "settings.h"

#include "details/response_time_statistics.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

ResponseTimeStatistics::ResponseTimeStatistics()
{}

ResponseTimeStatistics::~ResponseTimeStatistics()
{}

} // namespace fastcgi
