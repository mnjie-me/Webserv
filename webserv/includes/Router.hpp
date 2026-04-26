/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:27 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/26 13:04:24 by mari-cruz        ###   ########.fr       */
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
        std::string cgiQuery;
        std::string cgiPass;
        std::string indexFile;
        std::string uploadStore;
        bool autoindex;
    
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
        std::string getErrorUrl() const;
        std::pair<int, std::string> getredirectUrl() const;
        std::string getCgiPath() const;
        std::string getQuery() const;
        std::string getCgiPass() const;
        std::string getIndexFile() const;
        std::string getUploadStore() const;
        bool getAutoindex() const;       
};