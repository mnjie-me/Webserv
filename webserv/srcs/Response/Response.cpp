/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:40:24 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/27 11:58:51 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response() : statusCode(0), body("") {}

Response::Response(const Response& other)
{
    *this = other;
}

Response& Response::operator=(const Response& other)
{
    if (this != &other)
    {
        statusCode = other.statusCode;
        body = other.body;
        headers = other.headers;
    }
    return (*this);
}

Response::~Response() {}

std::string Response::toString() const
{
    std::map<int, std::string> statusMessages;
    statusMessages[200] = "OK";
    statusMessages[201] = "Created";
    statusMessages[204] = "No Content";
    statusMessages[301] = "Moved Permanently";
    statusMessages[400] = "Bad Request";
    statusMessages[403] = "Forbidden";
    statusMessages[404] = "Not Found";
    statusMessages[405] = "Method Not Allowed";
    statusMessages[413] = "Payload Too Large";
    statusMessages[500] = "Internal Server Error";
    statusMessages[505] = "HTTP Version Not Supported";

    std::string statusMsg = "Unknown";
    if (statusMessages.find(statusCode) != statusMessages.end())
        statusMsg = statusMessages[statusCode];

    std::string result = "HTTP/1.1 ";
    std::stringstream ss;
    ss << statusCode;
    result += ss.str() + " " + statusMsg + "\r\n";

    std::map<std::string, std::string>::const_iterator it = headers.begin();
    while (it != headers.end())
    {
        result += it->first + ": " + it->second + "\r\n";
        it++;
    }
    std::stringstream ss2;
    ss2 << body.size();
    result += "Content-Length: " + ss2.str() + "\r\n";
    result += "\r\n";
    result += body;
    return (result);
}