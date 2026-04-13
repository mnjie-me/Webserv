/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UtilsServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:20:01 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/12 12:59:25 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerConfig.hpp"
#include "UtilsServer.hpp"

void Request::setError(int code)
{
    errorCode = code;
    isValid = false;
}

int Request::getError() const
{
    return (errorCode);
}

bool Request::getIsValid() const
{
    return (isValid);
}
std::string Request::getMethod() const
{
    return (method);
}
std::string Request::getPath() const
{
    return (path);
}
std::string Request::getVersion() const
{
    return (version);
}
std::map<std::string, std::string> Request::getHeaders() const
{
    return (headers);
}
std::string Request::getBody() const
{
    return (body);
}

std::string trim(const std::string& line)
{
    size_t start = line.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos)
        return ("");
    size_t end = line.find_last_not_of(" \t\n\r\f\v");
    std::string trimmed = line.substr(start, end - start + 1);
    return (trimmed);
}
bool expectOpenBrace(std::ifstream& file)
{
    std::string line;
    while (getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#')
            continue ;
        if (trimmed == "{")
            return (true);
        return (false);
    }
    return (false);
}