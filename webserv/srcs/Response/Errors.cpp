/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:23:30 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/05/31 12:40:49 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"

Response Method::handleError(const Request& request, const Router& router)
{
    return buildError(request.getError(), router);
}

Response Method::buildError(int code, const Router& router)
{
    Response response;
    response.setStatusCode(code);
    std::map<int, std::string> errorPages = router.getErrorPages();
    std::map<int, std::string>::iterator it = errorPages.find(code);
    if (it != errorPages.end())
    {
        std::ifstream file(it->second.c_str());
        std::string line, buf;
        if (file.is_open())
        {
            while (std::getline(file, line))
                buf += line + '\n';
            file.close();
            response.setBody(buf);
            response.setHeader("Content-Type", "text/html");
            return response;
        }
    }
    response.setBody(defaultErrorPage(code));
    response.setHeader("Content-Type", "text/html");
    return response;
}

std::string Method::defaultErrorPage(int code)
{ 
    switch (code)
    {
        case 400: 
            return ("<html><h1>400 Bad Request</h1></html>");
        case 403:
            return ("<html><h1>403 Forbidden</h1></html>");
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