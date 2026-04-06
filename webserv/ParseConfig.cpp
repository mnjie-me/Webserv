/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:42:27 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/06 14:21:59 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

void ServerConfig::parseConfigFile(char *av)
{
    std::ifstream   file(av);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file" << std::endl;
        return ;
    }
    std::string line;
    std::vector<ServerConfig> servers;
    while (getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#')
            continue ;
        if (trimmed.substr(0, 6) == "server" && (trimmed.size() == 6
            || trimmed[6] == ' ' || trimmed[6] == '{'))
        {
            ServerConfig config;
            parseServer(config, file);
            servers.push_back(config);
        }
        else
        {
            std::cerr << "Error: unexpected token " << trimmed << std::endl;
            return ;
        }
    }
    file.close();
}

void ServerConfig::parseServer(ServerConfig& config, std::ifstream& file)
{
    std::string line;
    while (getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#')
            continue ;
        if (trimmed == "}" || trimmed == "};")
            return ;
        if (trimmed.substr(0, 6) == "listen")
        {
            std::string value = trim(trimmed.substr(6));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            char *end;
            long port = strtol(value.c_str(), &end, 10);
            if (*end != '\0')
            {
                std::cerr << "Error: invalid port" << std::endl;
                return ;
            }
            config.port = (int)port;
        }
        else if (trimmed.substr(0, 11) == "server_name")
        {
            std::string value = trim(trimmed.substr(11));
            if (value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            if (value.empty())
            {
                std::cerr << "Error: empty server name" << std::endl;
                return ;
            }
            config.serverName = value;
        }
        else if (trimmed.substr(0, 10) == "error_page")
        {
            std::string value = trim(trimmed.substr(10));
            size_t pos = value.find(' ');
            if (pos == std::string::npos)
            {
                std::cerr << "Error: error_page invalid format" << std::endl;
                return ;
            }
            std::string key = value.substr(0, pos);
            std::string val = trim(value.substr(pos));
            if (val[val.size() - 1] == ';')
                val.erase(val.size() - 1);
            if (val.empty())
            {
                std::cerr << "Error: empty error route" << std::endl;
                return ;
            }
            char *end;
            long errorNum = strtol(key.c_str(), &end, 10);
            if (*end != '\0')
            {
                std::cerr << "Error: invalid error code" << std::endl;
                return ;
            }
            config.errorPages[(int)errorNum] = val;
        }
    }
}

LocationConfig& LocationConfig::parseLocation(LocationConfig& config, std::ifstream& file)
{
    
}

std::string ServerConfig::trim(const std::string& line)
{
    size_t start = line.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos)
        return ("");
    size_t end = line.find_last_not_of(" \t\n\r\f\v");
    std::string trimmed = line.substr(start, end - start + 1);
    return (trimmed);
}