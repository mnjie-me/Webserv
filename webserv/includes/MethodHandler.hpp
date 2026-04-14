/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:26:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/14 20:59:25 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Request.hpp"
#include "Router.hpp"

class MethodHandler
{
    private:

        /* void handleGet
        void handlePost
        void handleDelete
        void handleCGI
        void handleAutoindex */

    public:

        MethodHandler();
        MethodHandler(const MethodHandler& other);
        MethodHandler& operator=(const MethodHandler& other);
        ~MethodHandler();
        
        void executeMethod(Request& request, const Router& router);
};