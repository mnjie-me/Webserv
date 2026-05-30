/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:14:07 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/12 18:13:06 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <cstdlib>

class ServerConfig;

class Request
{
    private:

        static const size_t                 MAX_REQUEST_SIZE = 8192;

        int                                 errorCode;
        bool                                isValid;
        std::string                         method;
        std::string                         path;
        std::string                         version;
        std::map<std::string, std::string>  headers;
        std::string                         body;
        
        void validateRequestLine();
        void validateHeaders();
        void validateBody(size_t clientMaxBodySize);
        
        public:
        
        
        Request();
        Request(const Request& other);
        Request& operator=(const Request& other);
        ~Request();
        
        void parseRequest(const std::string& raw, const ServerConfig& config);
        void setError(int code);
        int  getError() const;
        bool getIsValid() const;
        std::string getMethod() const;
        std::string getPath() const;
        std::string getVersion() const;
        std::map<std::string, std::string> getHeaders() const;
        std::string getBody() const;
};