/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:40:34 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/06 11:38:07 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConfig.hpp"

LocationConfig::LocationConfig() : autoindex(false) {}

LocationConfig::LocationConfig(const LocationConfig& other)
{
    *this = other;
}

LocationConfig& LocationConfig::operator=(const LocationConfig& other)
{
    if (this != &other)
    {
        root = other.root;
        methods = other.methods;
        index = other.index;
        autoindex = other.autoindex;
        uploadStore = other.uploadStore;
        redirect = other.redirect;
        cgiPass = other.cgiPass;
    }
    return (*this);
}

LocationConfig::~LocationConfig() {}