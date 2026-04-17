/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:18:01 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/17 13:48:49 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>

class Response
{
    private:
    
        int statusCode;    
        std::string body;
        std::map<std::string, std::string> headers;
    
    public:
    
        Response();
        Response(const Response& other);
        Response& operator=(const Response& other);
        ~Response();
        
        void setStatusCode(int code);
        void setBody(const std::string& body);
        void setHeader(const std::string& key, const std::string& value);

        int getStatusCode() const;
        std::string getBody() const;
        std::map<std::string, std::string> getHeaders() const;       
};