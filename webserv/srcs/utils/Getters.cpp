/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 19:51:25 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/14 20:10:19 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "Router.hpp"

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

std::string Router::getPath()const
{
    return (builtPath);
}
bool Router::getCGI()const
{
    return (CGI);
}
bool Router::getRedirect()const
{
    return (redirect);
}