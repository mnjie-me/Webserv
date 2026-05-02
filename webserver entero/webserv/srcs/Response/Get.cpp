/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:03:09 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/27 18:33:08 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"

Response Method::handleGet(const Request& request, const Router& router)
{
    Response response;
    struct stat info;

    if (stat(router.getPath().c_str(), &info) != 0)
    {
        response.setStatusCode(404);
        response.setBody(defaultErrorPage(404));
        response.setHeader("Content-Type", getContentType(router.getPath()));
        return (response);
    }
    if (S_ISDIR(info.st_mode))
    {
        if (!router.getIndexFile().empty())
        {
            std::string indexPath = router.getPath() + "/" + router.getIndexFile();
            if (stat(indexPath.c_str(), &info) == 0)
                return (handleIndex(indexPath, router));
        }
        if (router.getAutoindex())
            return (handleAutoindex(request, router));
        response.setStatusCode(403);
        response.setBody(defaultErrorPage(403));
        response.setHeader("Content-Type", getContentType(router.getPath()));
        return (response);      
    }
    std::ifstream file(router.getPath().c_str());
    if (!file.is_open())
    {
        response.setStatusCode(403);
        response.setBody(defaultErrorPage(403));
        response.setHeader("Content-Type", getContentType(router.getPath()));
        return (response);
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    response.setStatusCode(200);
    response.setBody(content);
    response.setHeader("Content-Type", getContentType(router.getPath()));
    return (response);
}

Response Method::handleIndex(std::string indexPath, const Router& router)
{
    Response response;
    std::ifstream file(indexPath.c_str());

    if (!file.is_open())
    {
        response.setStatusCode(403);
        response.setBody(defaultErrorPage(403));
        return (response);
    }
    std::string line;
    std::string content;
    while (getline(file, line))
    {
        content += line + '\n';
    }
    response.setStatusCode(200);
    response.setBody(content);
    response.setHeader("Content-Type", getContentType(router.getPath()));
    return (response);
}

Response Method::handleAutoindex(const Request& request, const Router& router)
{
    Response response;
    std::string autoindexBody = "<html><h1>Index of " + request.getPath() + "</h1><ul>";
    DIR* dir = opendir(router.getPath().c_str());
    if (dir == NULL)
        return (handleError(request, router));
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL)
    {
        std::string name = entry->d_name;
        if (name == "." || name == "..")
            continue;
        autoindexBody += "<li><a href=\"" + name + "\">" + name + "</a></li>";
    }
    closedir(dir);
    autoindexBody += "</ul></html>";
    response.setStatusCode(200);
    response.setBody(autoindexBody);
    response.setHeader("Content-Type", "text/html");
    return (response);
}

std::string Method::getContentType(const std::string& path)
{
    size_t pos = path.rfind('.');
    if (pos == std::string::npos)
        return ("text/plain");
    std::string ext = path.substr(pos);
    if (ext == ".html") 
        return ("text/html");
    if (ext == ".css")  
        return ("text/css");
    if (ext == ".js")   
        return ("application/javascript");
    if (ext == ".jpg" || ext == ".jpeg") 
        return ("image/jpeg");
    if (ext == ".png")  
        return ("image/png");
    if (ext == ".json") 
        return ("application/json");
    return ("text/plain");
}
