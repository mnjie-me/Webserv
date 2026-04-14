/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UtilsServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:20:01 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/14 19:51:47 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"
#include "UtilsServer.hpp"

std::string trim(const std::string& line)
{
    size_t start = line.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos)
        return ("");
    size_t end = line.find_last_not_of(" \t\n\r\f\v");
    std::string trimmed = line.substr(start, end - start + 1);
    return (trimmed);
}
bool expectOpenBrace(std::ifstream& file)
{
    std::string line;
    while (getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#')
            continue ;
        if (trimmed == "{")
            return (true);
        return (false);
    }
    return (false);
}