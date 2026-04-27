/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:33:39 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/27 12:03:58 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"

Response Method::handleDelete(const Router& router)
{
    Response response;
    struct stat info;
    
    if (stat(router.getPath().c_str(), &info) != 0)
    {
        response.setStatusCode(404);
        response.setBody(defaultErrorPage(404));
        response.setHeader("Content-Type", "text/html");
        return (response);
    }
    if (S_ISDIR(info.st_mode))
    {
        response.setStatusCode(403);
        response.setBody(defaultErrorPage(403));
        response.setHeader("Content-Type", "text/html");
        return (response);
    }
    if (remove(router.getPath().c_str()) != 0)
    {
        response.setStatusCode(500);
        response.setBody(defaultErrorPage(500));
        response.setHeader("Content-Type", "text/html");
        return (response);
    }
    response.setStatusCode(204);
    response.setHeader("Content-Type", "text/html");
    return (response);
}
