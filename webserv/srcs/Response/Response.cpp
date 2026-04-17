/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:40:24 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/17 14:15:47 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response() : statusCode(0), body("") {}

Response::Response(const Response& other)
{
    *this = other;
}

Response& Response::operator=(const Response& other)
{
    if (this != &other)
    {
        statusCode = other.statusCode;
        body = other.body;
        headers = other.headers;
    }
    return (*this);
}

Response::~Response() {}