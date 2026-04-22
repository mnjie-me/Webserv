/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 19:51:25 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/22 18:22:42 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "Router.hpp"
#include "Response.hpp"

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

std::string Router::getErrorUrl() const
{
    return (errorUrl);
}

std::pair<int, std::string> Router::getredirectUrl() const
{
    return (redirectUrl);
}

std::string Router::getCgiPath() const
{
    return (cgiPath);
}

std::string Router::getQuery() const
{
    return (cgiQuery);
}

std::string Router::getCgiPass() const
{
    return (cgiPass);
}

std::string Router::getIndexFile() const
{
    return (indexFile);
}

bool Router::getAutoindex() const
{
    return (autoindex);
}

int Response::getStatusCode() const
{
    return (statusCode);
}

std::string Response::getBody() const
{
    return (body);
}

const std::map<std::string, std::string>& Response::getHeaders() const
{
    return (headers);
}
