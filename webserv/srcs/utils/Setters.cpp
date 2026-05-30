/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:49:26 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/17 13:53:19 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "Request.hpp"

void Request::setError(int code)
{
    errorCode = code;
    isValid = false;
}

void Response::setStatusCode(int code)
{
    statusCode = code;
}

void Response::setBody(const std::string& b)
{
    body = b;
}

void Response::setHeader(const std::string& key, const std::string& value)
{
    headers[key] = value;
}

