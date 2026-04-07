/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:21:28 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/07 13:08:53 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerConfig.hpp"

Request::Request() : errorCode(0), isValid(true) {}

Request::Request(const Request& other)
{
    *this = other;
}

Request& Request::operator=(const Request& other)
{
    if (this != &other)
    {
        method = other.method;
        path = other.path;
        version = other.version;
        headers = other.headers;
        body = other.body;
        errorCode = other.errorCode;
        isValid = other.isValid;
    }
    return (*this);
}

Request::~Request() {}