/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 20:13:15 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/27 11:44:59 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"

Method::Method() {}

Method::Method(const Method& other)
{
    (void)other;
}

Method& Method::operator=(const Method& other)
{
    (void)other;
    return (*this);
}

Method::~Method() {}

Response Method::executeMethod(const Request& request, const Router& router)
{
    Response response;

    if (request.getError() != 0)
        return (handleError(request, router));
    else if (router.getCGI())
        return (handleCGI(request, router));
    else if (router.getRedirect())
        return (handleRedirect(router));
    return (handleMethod(request, router));
}

Response Method::handleRedirect(const Router& router)
{
    Response response;
    std::cout << "handle redirect" << std::endl;
    response.setStatusCode(router.getredirectUrl().first);
    response.setHeader("Location", router.getredirectUrl().second);
    return (response);
}

Response Method::handleMethod(const Request& request, const Router& router)
{
    Response response;
    
    if (request.getMethod() == "GET")
        return (handleGet(request, router));
    else if (request.getMethod() == "POST")
        return (handlePost(request, router));
    else if (request.getMethod() == "DELETE")
        return (handleDelete(router));
    return (response);
}


