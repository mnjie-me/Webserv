/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteMethod.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:32:42 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/17 14:20:52 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"

Response Method::executeMethod(const Request& request, const Router& router)
{
    Response response;
    
    if (request.getError() != 0)
    {
        handleError(request, router);
    }
/*
    else if (router.getCGI())
    {
        handleCGI(request);
    }
    else if (router.getRedirect())
    {
        handleRedirect(request)
    } */
    //std::cout << "<html><h1>404 Not Found</h1></html>" << std::endl;
    return (response);
}

Response Method::handleError(const Request& request, const Router& router)
{
    Response response;
    
    response.setStatusCode(request.getError());
    if (router.getErrorUrl().empty())
    {
        std::ifstream file(router.getErrorUrl().c_str());
        std::string   line;
        std::string   buf;
        if (!file.is_open())
        {
            response.setBody(defaultErrorPage(request.getError()));
        }
        else
        {
            while (std::getline(file, line))
                buf = line + '\n';
        }
        file.close();
    }
    else
    {
        response.setBody(defaultErrorPage(request.getError())); 
    }
    response.setHeader("Content-Type", "text/html");
    std::cout << response.getBody() << std::endl;
    return (response);
}

std::string Method::defaultErrorPage(int code)
{
    
    switch (code)
    {
        case 400: 
            return ("<html><h1>400 Bad Request</h1></html>"); 
        case 404: 
            return ("<html><h1>404 Not Found</h1></html>");
        case 405: 
            return ("<html><h1>405 Method Not Allowed</h1></html>");
        case 413: 
            return ("<html><h1>413 Payload Too Large</h1></html>");
        case 505: 
            return ("<html><h1>505 HTTP Version Not Supported</h1></html>");
        default:  
            return ("<html><h1>500 Internal Server Error</h1></html>"); 
    } 
}