/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:00:36 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/15 15:15:42 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"

Router::Router() : builtPath(""), CGI(false), redirect(false), errorUrl(""), cgiPath("") {}

Router::Router(const Router& other)
{
    *this = other;
}

Router& Router::operator=(const Router& other)
{
    if (this != &other)
    {
        this->builtPath = other.builtPath;
        this->CGI = other.CGI;
        this->redirect = other.redirect;
        this->redirectUrl = other.redirectUrl;
        this->errorUrl = other.errorUrl;
        this->cgiPath = other.cgiPath; 
    }
    return (*this);
}

Router::~Router() {}