/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:40:34 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/05 21:49:27 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConfig.hpp"

LocationConfig::LocationConfig() : autoindex(false) {}

LocationConfig::LocationConfig(const LocationConfig& other)
{
    this->autoindex = other.autoindex;
}

LocationConfig& LocationConfig::operator=(const LocationConfig& other)
{
    if (this != &other)
    {
        this->autoindex = other.autoindex;
    }
    return (*this);
}

LocationConfig::~LocationConfig() {}