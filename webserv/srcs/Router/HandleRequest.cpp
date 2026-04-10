/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:04:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/10 14:31:51 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"
#include "Router.hpp"

void Router::handleRequest(Request& request, const ServerConfig& config)
{
    const LocationConfig* loc = config.findLocation(request.getPath());
    if (loc == NULL)
    {
       request.setError(404);
        return ;
    }
    
}

const LocationConfig* ServerConfig::findLocation(const std::string& path) const
{
    std::map<std::string, LocationConfig>::const_iterator it = locations.begin();
    const LocationConfig* bestLoc = NULL;
    size_t len = 0;

    std::cout << path << std::endl;
    while (it != locations.end())
    {
        const std::string locPath = it->first;
        if (path.find(locPath) == 0 && locPath.size() > len)
        {
            bestLoc = &it->second;
            len = locPath.size();
        }
        it++;
    }
    return (bestLoc);
}

/* void ServerConfig::validateLoc()
{
    
} */