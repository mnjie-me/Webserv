/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:45:36 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/05 21:49:04 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

ServerConfig::ServerConfig() : port(8080), clientMaxBodySize(1048576) {}

ServerConfig::ServerConfig(const ServerConfig& other)
{
    this->port = other.port;
    this->clientMaxBodySize = other.clientMaxBodySize;
}

ServerConfig& ServerConfig::operator=(const ServerConfig& other)
{
    if (this != &other)
    {
        this->port = other.port;
        this->clientMaxBodySize = other.clientMaxBodySize;       
    }
    return (*this);
}

ServerConfig::~ServerConfig() {}