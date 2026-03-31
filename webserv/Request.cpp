/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:21:28 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/03/31 19:38:13 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request() : errorCode(0), isValid(true) {}

Request::Request(const Request& other)
{
    *this = other;
}

Request& Request::operator=(const Request& other)
{
    if (this != &other)
    {
        method = other.method;
        path = other.path;
        version = other.version;
        headers = other.headers;
        body = other.body;
        errorCode = other.errorCode;
        isValid = other.isValid;
    }
    return (*this);
}

Request::~Request() {}

void Request::parseRequest(const std::string& raw)
{
    size_t pos1;
    size_t pos2;
    size_t pos3;
    size_t pos4;
    
    if (raw.size() > MAX_REQUEST_SIZE)
    {
        setError(413);
        return;
    }
    size_t start = 0;
    while (start + 1 < raw.size() && raw[start] == '\r' && raw[start + 1] == '\n')
        start += 2;
    pos1 = raw.find(' ');
    if (pos1 == std::string::npos)
    {
        setError(400);
        return;
    }
    method = raw.substr(start, pos1 - start);
    pos2 = raw.find(' ', pos1 + 1);
    if (pos2 == std::string::npos)
    {
        setError(400);
        return;
    }
    path = raw.substr(pos1 + 1, pos2 - (pos1 + 1));
    pos3 = raw.find("\r\n", pos2 + 1);
    if (pos3 == std::string::npos)
    {
        setError(400);
        return;
    }
    if (pos3 > MAX_REQUEST_SIZE)
    {
        setError(414);
        return;
    }
    if (raw.find(' ', pos2 + 1) < pos3)
    {
        setError(400);
        return;
    }
    version = raw.substr(pos2 + 1, pos3 - (pos2 + 1));
    pos4 = raw.find("\r\n\r\n", pos3 + 2);
    if (pos4 == std::string::npos)
    {
        setError(400);
        return;
    }
    size_t start1 = pos3 + 2;
    while (start1 < pos4)
    {
        size_t end = raw.find("\r\n", start1);
        if (end == std::string::npos || end > pos4)
        {
            setError(400);
            return ;
        }
        std::string line = raw.substr(start1, end - start1);
        size_t split = line.find(':');
        if (split == std::string::npos)
        {
            setError(400);
            return;
        }
        std::string key = line.substr(0, split);
        std::string value = line.substr(split + 1);
        while (!key.empty() && (key[0] == ' ' || key[0] == '\t'))
            key.erase(0, 1);
        if (!key.empty() && (key[key.size() - 1] == ' '
            || key[key.size() - 1] == '\r' || key[key.size() - 1] == '\t'))
        {
            setError(404);
            return ;    
        }
        while (!value.empty() && (value[0] == ' ' || value[0] == '\t'))
            value.erase(0, 1);
        while (!value.empty() && (value[value.size() - 1] == ' '
            || value[value.size() - 1] == '\r' || value[value.size() - 1] == '\t'))
            value.erase(value.size() - 1);
        headers[key] = value;
        start = end + 2;
    }
    if (raw.size() >= 4 && pos4 <= raw.size() - 4)
        body = raw.substr(pos4 + 4);
    else
        body = "";
}

void Request::setError(int code)
{
    errorCode = code;
    isValid = false;
}

int Request::getError()
{
    return (errorCode);
}

void Request::validateRequestLine()
{
    if (method != "GET" && method != "POST" && method != "DELETE")
    {
        setError(405);
        return ;
    }
    if (path.empty() || path[0] != '/' || path.find("..") != std::string::npos)
    {
        setError(400);
        return ;
    }
    if (version != "HTTP/1.1")
    {
        setError(505);
        return ;
    }
}

void Request::validateHeaders()
{
    std::map<std::string, std::string>::iterator it1;
    std::map<std::string, std::string>::iterator it2;

    it1 = headers.find("Host");
    if (it1 == headers.end())
    {
        setError(400);
        return ;
    }
    if (it2 == headers.find("Content-Length"))
    {
        char *end;
        long size = std::strtol(it2->second.c_str(), &end, 10);
        if (*end != '\0')
        {
            setError(400);
            return ;
        }
        if (size != (long)body.size())
        {
            setError(400);
            return ;
        }
    } 
}
