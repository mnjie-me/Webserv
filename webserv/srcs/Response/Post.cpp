/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:05:35 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/26 13:47:12 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"

Response Method::handlePost(const Request& request, const Router& router)
{
    Response response;

    if (router.getUploadStore().empty())
    {
        response.setStatusCode(403);
        response.setBody(defaultErrorPage(403));
        response.setHeader("Content-Type", "text/html");
        return response;
    }
    if (request.getBody().empty())
    {
        response.setStatusCode(400);
        response.setBody(defaultErrorPage(400));
        response.setHeader("Content-Type", "text/html");
        return response;
    }
    std::string fileName = createFileName();
    std::string fullPath = router.getUploadStore() + "/" + fileName;
    std::ofstream file(fullPath.c_str());
    if (!file.is_open())
    {
        response.setStatusCode(500);
        response.setBody(defaultErrorPage(500));
        response.setHeader("Content-Type", "text/html");
        return response;
    }
    file << request.getBody();
    file.close();
    response.setStatusCode(201);
    response.setBody("File uploaded: " + fileName);
    response.setHeader("Content-Type", "text/plain");
    return (response);
}

std::string Method::createFileName()
{
    static int counter = 0;
    time_t t = time(NULL);
    std::stringstream ss;
    ss << t << "_" << counter++;
    std::string fileName = "upload_" + ss.str() + ".txt";
    std::cout << fileName << std::endl;
    return (fileName);
}
