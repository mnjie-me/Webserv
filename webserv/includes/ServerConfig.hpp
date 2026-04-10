/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:35:29 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/10 14:30:36 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include "LocationConfig.hpp"
#include "UtilsServer.hpp"

class ServerConfig
{
    public:

        int                                     port;
        std::string                             serverName;
        size_t                                  clientMaxBodySize;
        std::map<int, std::string>              errorPages;
        std::map<std::string, LocationConfig>   locations;

        ServerConfig();
        ServerConfig(const ServerConfig& other);
        ServerConfig& operator=(const ServerConfig& other);
        ~ServerConfig();

        void parseConfigFile(char *av);
        bool parseServer(ServerConfig& config, std::ifstream& file);
        const LocationConfig* findLocation(const std::string& path) const;
};