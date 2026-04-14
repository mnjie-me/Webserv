/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:00:36 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/14 20:30:06 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"

Router::Router() : builtPath (""), CGI(false), redirect(false) {}

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
    }
    return (*this);
}

Router::~Router() {}