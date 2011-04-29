// Fastcgi Daemon - framework for design highload FastCGI applications on C++
// Copyright (C) 2011 Ilya Golubtsov <golubtsov@yandex-team.ru>

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef _FASTCGI_DETAILS_REQUEST_FILTER_H_
#define _FASTCGI_DETAILS_REQUEST_FILTER_H_

#include <string>

#include <boost/regex.hpp>


namespace fastcgi
{

class Request;

class RequestFilter {
public:
    virtual bool check(const Request *request) const = 0;
};

class RegexFilter  {
public:
    RegexFilter(const std::string &regex);
    ~RegexFilter();

    bool check(const std::string &value) const;
private:
    boost::regex regex_;
};

class UrlFilter : public RequestFilter {
public:
    UrlFilter(const std::string &regex);
    ~UrlFilter();

    virtual bool check(const Request *request) const;
private:
    RegexFilter regex_;
};

class HostFilter : public RequestFilter {
public:
    HostFilter(const std::string &regex);
    ~HostFilter();

    virtual bool check(const Request *request) const;
private:
    RegexFilter regex_;
};

class PortFilter : public RequestFilter {
public:
    PortFilter(const std::string &regex);
    ~PortFilter();

    virtual bool check(const Request *request) const;
private:
    RegexFilter regex_;
};

class AddressFilter : public RequestFilter {
public:
    AddressFilter(const std::string &regex);
    ~AddressFilter();

    virtual bool check(const Request *request) const;
private:
    RegexFilter regex_;
};

class ParamFilter : public RequestFilter {
public:
    ParamFilter(const std::string &name, const std::string &regex);
    ~ParamFilter();

    virtual bool check(const Request *request) const;
private:
    std::string name_;
    RegexFilter regex_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_REQUEST_FILTER_H_
