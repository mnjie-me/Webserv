/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:26:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/17 14:05:40 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <string>

#include "Request.hpp"
#include "Router.hpp"
#include "Response.hpp"

class Method
{
    private:

        std::string body;

        Response handleError(const Request& request, const Router& router);
        /* void handleGet
        void handlePost
        void handleDelete
        void handleCGI
        void handleAutoindex */

    public:

        Method();
        Method(const Method& other);
        Method& operator=(const Method& other);
        ~Method();
        
        Response executeMethod(const Request& request, const Router& router);
        std::string defaultErrorPage(int code);
};