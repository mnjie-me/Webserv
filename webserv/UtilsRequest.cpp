/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UtilsRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:20:01 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/01 13:35:46 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

void Request::setError(int code)
{
    errorCode = code;
    isValid = false;
}

int Request::getError()
{
    return (errorCode);
}

bool Request::getIsValid()
{
    return (isValid);
}
std::string Request::getMethod()
{
    return (method);
}
std::string Request::getPath()
{
    return (path);
}
std::string Request::getVersion()
{
    return (version);
}
std::map<std::string, std::string> Request::getHeaders()
{
    return (headers);
}
std::string Request::getBody()
{
    return (body);
}