/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:26:53 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/26 13:47:35 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
#include <ctime>

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
        Response handleRedirect(const Router& router);
        Response handleMethod(const Request& request, const Router& router);
        Response handleGet(const Request& request, const Router& router);
        Response handlePost(const Request& request, const Router& router);
        Response handleDelete(const Request& request, const Router& router);
        Response handleIndex(std::string indexPath, const Router& router);
        
        Response handleAutoindex(const Request& request, const Router& router);
        std::string getContentType(const std::string& path);
        char** vecToCharArray(const std::vector<std::string>& env);
        std::string defaultErrorPage(int code);
        std::string getInterpreter(const Router& router);
        std::string createFileName();

    public:

        Method();
        Method(const Method& other);
        Method& operator=(const Method& other);
        ~Method();
        
        Response executeMethod(const Request& request, const Router& router);
};