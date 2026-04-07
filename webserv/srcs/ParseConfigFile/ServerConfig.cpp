/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:45:36 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/06 11:40:02 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

ServerConfig::ServerConfig() : port(8080), clientMaxBodySize(1048576) {}

ServerConfig::ServerConfig(const ServerConfig& other)
{
    *this = other;
}

ServerConfig& ServerConfig::operator=(const ServerConfig& other)
{
    if (this != &other)
    {
        port = other.port;
        serverName = other.serverName;
        clientMaxBodySize = other.clientMaxBodySize;
        errorPages = other.errorPages;
        locations = other.locations;       
    }
    return (*this);
}

ServerConfig::~ServerConfig() {}