/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:22:09 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/05 13:38:42 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

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
    pos1 = raw.find(' ', start);
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
    size_t startLine = pos3 + 2;
    while (startLine < pos4)
    {
        size_t end = raw.find("\r\n", startLine);
        if (end == std::string::npos || end > pos4)
        {
            setError(400);
            return ;
        }
        std::string line = raw.substr(startLine, end - startLine);
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
            setError(400);
            return ;    
        }
        while (!value.empty() && (value[0] == ' ' || value[0] == '\t'))
            value.erase(0, 1);
        while (!value.empty() && (value[value.size() - 1] == ' '
            || value[value.size() - 1] == '\r' || value[value.size() - 1] == '\t'))
            value.erase(value.size() - 1);
        headers[key] = value;
        startLine = end + 2;
    }
    if (raw.size() >= 4 && pos4 <= raw.size() - 4)
        body = raw.substr(pos4 + 4);
    else
        body = "";
    validateRequestLine();
    if (!isValid)
        return ;
    validateHeaders();
    if (!isValid)
        return ;
    validateBody();
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
    if (it1 == headers.end() || it1->second.empty())
    {
        setError(400);
        return ;
    }
    it2 = headers.find("Content-Length");
    if (it2 != headers.end())
    {
        char *end;
        long size = std::strtol(it2->second.c_str(), &end, 10);
        if (size < 0 || *end != '\0' || size != (long)body.size())
        {
            setError(400);
            return ;
        }
    } 
}

void Request::validateBody(size_t clientMaxBodySize)
{
    if (body.size() > clientMaxBodySize)
    {
        setError(413);
        return ;
    }
}