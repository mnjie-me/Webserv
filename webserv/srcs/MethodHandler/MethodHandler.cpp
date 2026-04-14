/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 20:13:15 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/14 21:00:28 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodHandler.hpp"

MethodHandler::MethodHandler() {}

MethodHandler::MethodHandler(const MethodHandler& other)
{
    (void)other;
}

MethodHandler& MethodHandler::operator=(const MethodHandler& other)
{
    (void)other;
    return (*this);
}

MethodHandler::~MethodHandler() {}

void MethodHandler::executeMethod(Request& request, const Router& router)
{
    (void)request;
    (void)router;
    std::cout << "<html><h1>404 Not Found</h1></html>" << std::endl;
}
