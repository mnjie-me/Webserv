/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteMethod.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:32:42 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/21 13:03:22 by mari-cruz        ###   ########.fr       */
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
    else if (router.getCGI())
    {
        handleCGI(request, router);
    }
    /*
    else if (router.getRedirect())
    {
        handleRedirect(request)
    } */
    //std::cout << "<html><h1>404 Not Found</h1></html>" << std::endl;
    return (response);
}



