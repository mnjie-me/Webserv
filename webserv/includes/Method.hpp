/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:26:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/21 13:03:41 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>

#include "LocationConfig.hpp"
#include "Request.hpp"
#include "Router.hpp"
#include "Response.hpp"

class Method
{
    private:

        std::string body;

        Response handleError(const Request& request, const Router& router);
        Response handleCGI(const Request& request, const Router& router);
        Response readCgiOutput(int* fd, Response& response, pid_t pid);
        /* void handleGet
        void handlePost
        void handleDelete
        void handleCGI
        void handleAutoindex */
        char** vecToCharArray(const std::vector<std::string>& env);
        std::string defaultErrorPage(int code);
        std::string getInterpreter(const Router& router);

    public:

        Method();
        Method(const Method& other);
        Method& operator=(const Method& other);
        ~Method();
        
        Response executeMethod(const Request& request, const Router& router);
};