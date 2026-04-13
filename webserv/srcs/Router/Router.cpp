/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:00:36 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/12 13:02:22 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"

Router::Router() {}

Router::Router(const Router& other)
{
    (void)other;
}

Router& Router::operator=(const Router& other)
{
    (void)other;
    return (*this);
}

Router::~Router() {}