/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:18:01 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/07 13:11:25 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>

class Response
{
    public:
    
        Response();
        Response(const Response& other);
        Response operator=(const Response& other);
        
        int statusCode;    
        std::string body;
        std::map<std::string, std::string> header;
};