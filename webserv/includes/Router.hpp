/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:27 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/15 15:15:12 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include "ServerConfig.hpp"
#include "LocationConfig.hpp"
#include "UtilsServer.hpp"

class Router
{
    private:

        std::string builtPath;
        bool        CGI;
        bool        redirect;
        std::string errorUrl;
        std::pair<int, std::string> redirectUrl;
        std::string cgiPath;
    
        bool handleRedirect(Request& request, const LocationConfig& loc);
        bool validateMethod(Request& request, const ServerConfig& config, const LocationConfig& loc);
        std::string buildPath(Request& request, const LocationConfig& loc, std::string matchedPath);
        bool isCGI(const std::string& path, const LocationConfig& loc);
        void saveErrorUrl(Request& request, const ServerConfig& config);

        
    public:
    
        Router();
        Router(const Router& other);
        Router& operator=(const Router& other);
        ~Router();
        
        void handleRequest(Request& request, const ServerConfig& config);
        std::string getPath()const;
        bool getCGI()const;
        bool getRedirect()const;
    
};