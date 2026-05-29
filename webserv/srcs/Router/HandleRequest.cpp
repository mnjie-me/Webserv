/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:04:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/05/29 16:17:51 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"

Router::Router() : builtPath(""), CGI(false), redirect(false), cgiPath(""), cgiQuery (""), cgiPass("") {}

Router::Router(const Router& other)
{
    *this = other;
}

Router& Router::operator=(const Router& other)
{
    if (this != &other)
    {
        this->builtPath = other.builtPath;
        this->CGI = other.CGI;
        this->redirect = other.redirect;
        this->redirectUrl = other.redirectUrl;
        this->cgiPath = other.cgiPath;
        this->cgiQuery = other.cgiQuery;
        this->cgiPass = other.cgiPass;
    }
    return (*this);
}

Router::~Router() {}

void Router::handleRequest(Request& request, const ServerConfig& config)
{
    errorPages = config.errorPages;
    std::string matchedPath;
    const LocationConfig* loc = config.findLocation(request.getPath(), matchedPath);
    std::map<int, std::string>::const_iterator it;

    if (request.getError() != 0)
        return;
    if (loc == NULL)
    {
        request.setError(404);
        return ;
    }
    redirect = handleRedirect(request, *loc);
    if (redirect)
        return ;
    if (!validateMethod(request, *loc))
        return ;
    builtPath = buildPath(request, *loc, matchedPath);
    indexFile = loc->index;
    autoindex = loc->autoindex;
    uploadStore =  loc->uploadStore;
    CGI = isCGI(builtPath, *loc);
    if (CGI)
    {
        cgiPass = loc->cgiPass;
        return ;
    }
}

const LocationConfig* ServerConfig::findLocation(const std::string& path, std::string& matchedPath) const
{
    std::map<std::string, LocationConfig>::const_iterator it = locations.begin();
    const LocationConfig* bestLoc = NULL;
    size_t len = 0;

    it = locations.begin();
    while (it != locations.end())
    {
        const std::string locPath = it->first;
        if (path.find(locPath) == 0 && locPath.size() > len)
        {
            bestLoc = &it->second;
            len = locPath.size();
            matchedPath = locPath;
        }
        it++;
    }
    return (bestLoc);
}


bool Router::handleRedirect(Request& request, const LocationConfig& loc)
{
    (void)request;
    if (loc.redirect.second.empty())
        return (false);
    redirectUrl.first = loc.redirect.first;
    redirectUrl.second = loc.redirect.second;
    return (true);
}


bool Router::validateMethod(Request& request, const LocationConfig& loc)
{
    if (loc.methods.empty())
        return (true);
    size_t i = 0;

    while (i < loc.methods.size())
    {
        if (loc.methods[i] == request.getMethod())
            return (true);
        i++;
    }
    request.setError(405);
    return (false);
}

std::string Router::buildPath(Request& request, const LocationConfig& loc, std::string matchedPath)
{    
    std::string value = request.getPath().substr(matchedPath.size());
    if (value.empty() || value[0] != '/')
        value = "/" + value;
    std::string fullPath = loc.root + value;
    return (fullPath);
}

bool Router::isCGI(const std::string& path, const LocationConfig& loc)
{
    cgiPath = path;
    if (loc.cgiPass.empty())
        return (false);
    size_t pos = path.rfind('?');
    if (pos != std::string::npos)
        cgiQuery = path.substr(pos + 1);
    size_t pos1 = path.rfind('.');
    if (pos1 == std::string::npos)
        return (false);
    std::string value = path.substr(pos1);
    if (value == loc.cgiPass)
        return (true);
    return (false);
}
