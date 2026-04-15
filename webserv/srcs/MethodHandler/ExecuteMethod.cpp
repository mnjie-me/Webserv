/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteMethod.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:32:42 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/15 14:25:03 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodHandler.hpp"

void MethodHandler::executeMethod(Request& request, const Router& router)
{
    (void)request;
    (void)router;
/* 
    if (request.getError() != 0)
    {
        handleError(request);
    }
    else if (router.getCGI())
    {
        handleCGI(request);
    }
    else if (router.getRedirect())
    {
        handleRedirect(request)
    } */
    //std::cout << "<html><h1>404 Not Found</h1></html>" << std::endl;
}