/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:21:28 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/03/30 22:02:11 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request() {}

Request::Request(const Request& other)
{
    *this = other;
}

Request& Request::operator=(const Request& other)
{
    if (this != &other)
    {
        method = other.method;
        path = other.path;
        version = other.version;
        headers = other.headers;
        body = other.body;
    }
    return (*this);
}

void Request::parseRequest(const std::string& raw)
{
    size_t pos1;
    size_t pos2;
    size_t pos3;
    size_t pos4;

    pos1 = raw.find(' ');
    method = raw.substr(0, pos1);
    std::cout << method << std::endl;
    pos2 = raw.find(' ', pos1 + 1);
    path = raw.substr(pos1 + 1, pos2 - (pos1 + 1));
    std::cout << path << std::endl;
    pos3 = raw.find("\r\n", pos2 + 1);
    version = raw.substr(pos2 + 1, pos3 - (pos2 + 1));
    std::cout << version << std::endl;
    pos4 = raw.find("\r\n\r\n", pos3 + 1);
    size_t start = pos3 + 2;
    while (start < pos4)
    {
        size_t end = raw.find("\r\n", start);
        if (end == std::string::npos || end > pos4)
            break;
        std::string line = raw.substr(start, end - start);
        size_t split = line.find(':');
        if (split != std::string::npos)
        {
            std::string key = line.substr(0, split);
            std::string value = line.substr(split + 1);
            while (!key.empty() && (key[0] == ' ' || key[0] == '\r' || key[0] == '\t'))
                key.erase(0, 1);
            while (!value.empty() && value[0] == ' ')
                value.erase(0, 1);
            headers[key] = value;
            std::cout << "Header: [" << line << "]" << std::endl;
        }
        start = end + 2;
    }
    if (pos4 == std::string::npos)
        body = "";
    else if (pos4 + 4 < raw.size())
        body = raw.substr(pos4 + 4);
    else
        body = "";
    std::cout << body << std::endl;
}

/* Añadir el campo de error y cambiar parseRequest para que retorne o setee ese estado
Validar cada find antes de usarlo
Limpiar trailing whitespace en valores de header
Poner un límite en longitud de request line y número de headers
Luego ya lo que dices tú — verificar method válido, path válido, versión, headers obligatorios como Host, etc.

 */