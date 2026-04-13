/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:27 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/13 13:16:50 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include "ServerConfig.hpp"
#include "LocationConfig.hpp"

class Router
{
    private:
    
        bool handleRedirect(Request& request, const LocationConfig& loc);
        bool validateMethod(Request& request, const LocationConfig& loc);
        std::string buildPath(Request& request, const LocationConfig& loc, std::string matchedPath);
        bool isCGI(const std::string& path, const LocationConfig& loc);
        
    public:
    
        Router();
        Router(const Router& other);
        Router& operator=(const Router& other);
        ~Router();
        
        void handleRequest(Request& request, const ServerConfig& config);
    
};