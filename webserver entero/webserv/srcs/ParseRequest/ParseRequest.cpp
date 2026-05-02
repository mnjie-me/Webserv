/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:22:09 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/05/02 18:23:51 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerConfig.hpp"

void Request::parseRequest(const std::string& raw, const ServerConfig& config)
{
    size_t pos1;
    size_t pos2;
    size_t pos3;

    if (raw.size() > MAX_REQUEST_SIZE)
    {
        setError(413);
        return;
    }
    size_t start = 0;
    while (start + 1 < raw.size() && raw[start] == '\r' && raw[start + 1] == '\n')
        start += 2;

    // Extraer method
    pos1 = raw.find(' ', start);
    if (pos1 == std::string::npos)
    {
        setError(400);
        return;
    }
    method = raw.substr(start, pos1 - start);

    // Extraer path
    pos2 = raw.find(' ', pos1 + 1);
    if (pos2 == std::string::npos)
    {
        setError(400);
        return;
    }
    path = raw.substr(pos1 + 1, pos2 - (pos1 + 1));
    std::cout << path << std::endl;

    // Fin de la request line (primera linea solamente)
    pos3 = raw.find("\r\n", pos2 + 1);
    size_t lineStep = 2;
    if (pos3 == std::string::npos)
    {
        pos3 = raw.find('\n', pos2 + 1);
        lineStep = 1;
    }
    if (pos3 == std::string::npos)
    {
        setError(400);
        return;
    }

    // Verificar que no hay espacios extra en la request line
    if (raw.find(' ', pos2 + 1) < pos3)
    {
        setError(400);
        return;
    }

    // Extraer version (solo hasta el fin de la primera linea)
    version = raw.substr(pos2 + 1, pos3 - (pos2 + 1));
    if (!version.empty() && version[version.size() - 1] == '\r')
        version.erase(version.size() - 1);

    // Fin de los headers (doble salto de linea)
    size_t headersEnd = raw.find("\r\n\r\n");
    size_t bodyOffset = 4;
    if (headersEnd == std::string::npos)
    {
        headersEnd = raw.find("\n\n");
        bodyOffset = 2;
    }
    if (headersEnd == std::string::npos)
    {
        setError(400);
        return;
    }

    // Parsear headers
    size_t startLine = pos3 + lineStep;
    while (startLine < headersEnd)
    {
        size_t end = raw.find("\r\n", startLine);
        size_t step = 2;
        if (end == std::string::npos || end > headersEnd)
        {
            end = raw.find('\n', startLine);
            step = 1;
        }
        if (end == std::string::npos || end > headersEnd)
        {
            setError(400);
            return;
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
            return;
        }
        while (!value.empty() && (value[0] == ' ' || value[0] == '\t'))
            value.erase(0, 1);
        while (!value.empty() && (value[value.size() - 1] == ' '
            || value[value.size() - 1] == '\r' || value[value.size() - 1] == '\t'))
            value.erase(value.size() - 1);

        headers[key] = value;
        startLine = end + step;
    }

    // Extraer body
    if (raw.size() >= bodyOffset && headersEnd <= raw.size() - bodyOffset)
        body = raw.substr(headersEnd + bodyOffset);
    else
        body = "";

    validateRequestLine();
    if (!isValid)
        return;
    validateHeaders();
    if (!isValid)
        return;
    validateBody(config.clientMaxBodySize);
}

void Request::validateRequestLine()
{
    if (method != "GET" && method != "POST" && method != "DELETE")
    {
        setError(405);
        return;
    }
    if (path.empty() || path[0] != '/' || path.find("..") != std::string::npos)
    {
        setError(400);
        return;
    }
    if (version != "HTTP/1.1")
    {
        setError(505);
        return;
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
        return;
    }
    it2 = headers.find("Content-Length");
    if (it2 != headers.end())
    {
        char *end;
        long size = std::strtol(it2->second.c_str(), &end, 10);
        if (size < 0 || *end != '\0' || size != (long)body.size())
        {
            setError(400);
            return;
        }
    }
}

void Request::validateBody(size_t clientMaxBodySize)
{
    if (body.size() > clientMaxBodySize)
    {
        setError(413);
        return;
    }
}