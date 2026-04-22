/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:04:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/22 18:52:29 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"

void Router::handleRequest(Request& request, const ServerConfig& config)
{
    std::string matchedPath;
    const LocationConfig* loc = config.findLocation(request.getPath(), matchedPath);
    std::map<int, std::string>::const_iterator it;
    
    if (loc == NULL)
    {
        request.setError(404);
        saveErrorUrl(request, config);
        return ;
    }
    redirect = handleRedirect(request, *loc);
    if (redirect)
        return ;
    if (!validateMethod(request, config, *loc))
        return ;
    builtPath = buildPath(request, *loc, matchedPath);
    indexFile = loc->index;
    autoindex = loc->autoindex;
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

void Router::saveErrorUrl(Request& request, const ServerConfig& config)
{
    std::map<int, std::string>::const_iterator it;
    
    it = config.errorPages.find(request.getError());
    if (it != config.errorPages.end())
        errorUrl = it->second;
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


bool Router::validateMethod(Request& request, const ServerConfig& config, const LocationConfig& loc)
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
    saveErrorUrl(request, config);
    return (false);
}

std::string Router::buildPath(Request& request, const LocationConfig& loc, std::string matchedPath)
{    
    std::string value = request.getPath().substr(matchedPath.size());
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
