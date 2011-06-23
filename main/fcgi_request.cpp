#include "settings.h"

#include <cstring>

#include <boost/lexical_cast.hpp>

#include "endpoint.h"
#include "fcgi_request.h"

#include "fastcgi2/logger.h"
#include "fastcgi2/request.h"

#include "details/response_time_statistics.h"

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

namespace fastcgi
{

static const std::string DAEMON_STRING = "fastcgi-daemon";

FastcgiRequest::FastcgiRequest(boost::shared_ptr<Request> request, Endpoint *endpoint,
        Logger *logger, ResponseTimeStatistics *statistics, const bool logTimes) :
    request_(request), logger_(logger), endpoint_(endpoint),
    statistics_(statistics), logTimes_(logTimes), handler_(NULL)
{
    if (0 != FCGX_InitRequest(&fcgiRequest_, endpoint_->socket(), 0)) {
        throw std::runtime_error("can not init fastcgi request");
    }
}

FastcgiRequest::~FastcgiRequest() {
    boost::uint64_t microsec = 0;
    if (logTimes_ || statistics_) {
        gettimeofday(&finish_time_, NULL);

        microsec = (finish_time_.tv_sec - accept_time_.tv_sec) *
            1000000 + (finish_time_.tv_usec - accept_time_.tv_usec);
    }

    if (logTimes_) {
        double res = static_cast<double>(microsec) / 1000000.0;
        logger_->info("handling %s taken %08f seconds", url_.c_str(), res);
    }

    if (statistics_) {
        try {
            statistics_->add(handler_ ? handler_->id : DAEMON_STRING, request_->status(), microsec);
        }
        catch (const std::exception &e) {
            logger_->error("Exception caught while update statistics: %s", e.what());
        }
        catch (...) {
            logger_->error("Unknown exception caught while update statistics");
        }
    }

    FCGX_Finish_r(&fcgiRequest_);
}

void
FastcgiRequest::attach() {
    request_->attach(this, fcgiRequest_.envp);
    char **envp = fcgiRequest_.envp;
    for (std::size_t i = 0; envp[i]; ++i) {
        if (0 == strncasecmp(envp[i], "REQUEST_URI=", sizeof("REQUEST_URI=") - 1)) {
            url_.assign(envp[i] + sizeof("REQUEST_URI=") - 1);
            break;
        }
    }
}

int
FastcgiRequest::accept() {
    int status = FCGX_Accept_r(&fcgiRequest_);
    if (status >= 0 && (logTimes_|| statistics_)) {
        gettimeofday(&accept_time_, NULL);
    }
    return status;
}

int
FastcgiRequest::read(char *buf, int size) {
    return FCGX_GetStr(buf, size, fcgiRequest_.in);
}

int
FastcgiRequest::write(const char *buf, int size) {
    int num = FCGX_PutStr(buf, size, fcgiRequest_.out);
    if (-1 == num) {
        int error = FCGX_GetError(fcgiRequest_.out);
        if (error > 0) {
            char buffer[256];
            std::stringstream str;
            str << "Cannot write data to fastcgi socket: " <<
                strerror_r(error, buffer, sizeof(buffer));
            str << ". Url: " << request_->getUrl();
            throw std::runtime_error(str.str());
        }
        throw std::runtime_error("FastCGI error. Url: " + request_->getUrl());
    }
    return num;
}

void
FastcgiRequest::write(std::streambuf *buf) {
    std::vector<char> outv(4096);
    fcgi_streambuf outbuf(fcgiRequest_.out, &outv[0], outv.size());
    std::ostream os(&outbuf);
    os << buf;
}

void
FastcgiRequest::setHandlerDesc(const HandlerSet::HandlerDescription *handler) {
    handler_ = handler;
}

} // namespace fastcgi
