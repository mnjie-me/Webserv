/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:04:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/14 20:59:58 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"
#include "Router.hpp"

void Router::handleRequest(Request& request, const ServerConfig& config)
{
    std::string matchedPath;
    const LocationConfig* loc = config.findLocation(request.getPath(), matchedPath);
    
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
    CGI = isCGI(builtPath, *loc);
    if (CGI)
        return ;
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
    if (loc.redirect.second.empty())
        return (false);
    request.setError(loc.redirect.first);
    return (true);
}


bool Router::validateMethod(Request& request, const LocationConfig& loc)
{
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
    std::string fullPath = loc.root + value;
    return (fullPath);
}

bool Router::isCGI(const std::string& path, const LocationConfig& loc)
{
    if (loc.cgiPass.empty())
        return (false);
    size_t pos = path.rfind('.');
    if (pos == std::string::npos)
        return (false);
    std::string value = path.substr(pos);
    if (value == loc.cgiPass)
        return (true);
    return (false);
}