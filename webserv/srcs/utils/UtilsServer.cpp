/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UtilsServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:20:01 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/07 13:14:46 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerConfig.hpp"

void Request::setError(int code)
{
    errorCode = code;
    isValid = false;
}

int Request::getError()
{
    return (errorCode);
}

bool Request::getIsValid()
{
    return (isValid);
}
std::string Request::getMethod()
{
    return (method);
}
std::string Request::getPath()
{
    return (path);
}
std::string Request::getVersion()
{
    return (version);
}
std::map<std::string, std::string> Request::getHeaders()
{
    return (headers);
}
std::string Request::getBody()
{
    return (body);
}

std::string ServerConfig::trim(const std::string& line)
{
    size_t start = line.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos)
        return ("");
    size_t end = line.find_last_not_of(" \t\n\r\f\v");
    std::string trimmed = line.substr(start, end - start + 1);
    return (trimmed);
}