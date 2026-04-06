/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:36:49 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/06 13:10:38 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class LocationConfig
{
    public:
        std::string                 root;
        std::vector<std::string>    methods;
        std::string                 index;
        bool                        autoindex;
        std::string                 uploadStore;
        std::string                 redirect;
        std::string                 cgiPass;

        LocationConfig();
        LocationConfig(const LocationConfig& other);
        LocationConfig& operator=(const LocationConfig& other);
        ~LocationConfig();

        LocationConfig& parseLocation(LocationConfig& config, std::ifstream& file);
};