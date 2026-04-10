/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:27 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/10 14:32:02 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include "ServerConfig.hpp"
#include "LocationConfig.hpp"

class Router
{
    private:
    
        void validateMethod(const Request& request, const LocationConfig& loc);
        void validateBodySize(const Request& request, const ServerConfig& config);
        void handleRedirect(const LocationConfig& loc);
        std::string buildPath(const Request& request, const LocationConfig& loc);
        bool isCGI(const std::string& path, const LocationConfig& loc);
        
    public:
    
        Router();
        ~Router();
        
        void handleRequest(Request& request, const ServerConfig& config);
    
};