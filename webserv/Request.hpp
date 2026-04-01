/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:14:07 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/01 13:33:31 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <cstdlib>

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
        void setError(int code);
        
        public:
        
        
        Request();
        Request(const Request& other);
        Request& operator=(const Request& other);
        ~Request();
        
        void parseRequest(const std::string& raw);
        int  getError();
        bool getIsValid();
        std::string getMethod();
        std::string getPath();
        std::string getVersion();
        std::map<std::string, std::string> getHeaders();
        std::string getBody();
};