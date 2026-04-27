/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:42:27 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/27 18:17:53 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"
#include "LocationConfig.hpp"

//hacer función boolean

void ServerConfig::parseConfigFile(char *av, std::vector<ServerConfig>& servers)
{
    std::ifstream   file(av);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file" << std::endl;
        return ;
    }
    std::string line;
    while (getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#')
            continue ;
        if (trimmed.substr(0, 6) == "server" && (trimmed.size() == 6
            || trimmed[6] == ' ' || trimmed[6] == '{'))
        {
            if (trimmed.find('{') == std::string::npos && !expectOpenBrace(file))
            {
                std::cerr << "Error: server block not opened" << std::endl;
                return ;
            }
            ServerConfig config;
            if (!parseServer(config, file))
                return ;
            servers.push_back(config);
        }
        else if (trimmed == "}" || trimmed == "};")
            continue ;
        else
        {
            std::cerr << "Error: unexpected token " << trimmed << std::endl;
            return ;
        }
    }
    file.close();
    if (servers.empty())
    {
        std::cerr << "Error: no server configured" << std::endl;
        return ;
    }
}

bool ServerConfig::parseServer(ServerConfig& config, std::ifstream& file)
{
    std::string line;
    
    while (getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#')
            continue ;
        if (trimmed == "}" || trimmed == "};")
            return (true);
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
                return (false);
            }
            if (port < 1 || port > 65535)
            {
                std::cerr << "Error: port out of range" << std::endl;
                return (false);
            }
            config.port = static_cast<int>(port);
        }
        else if (trimmed.substr(0, 11) == "server_name")
        {
            std::string value = trim(trimmed.substr(11));
            if (value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            if (value.empty())
            {
                std::cerr << "Error: empty server name" << std::endl;
                return (false);
            }
            config.serverName = value;
        }
        else if (trimmed.substr(0, 10) == "error_page")
        {
            std::string value = trim(trimmed.substr(10));
            size_t pos = value.find(' ');
            if (pos == std::string::npos)
            {
                std::cerr << "Error: invalid error page format" << std::endl;
                return (false);
            }
            std::string key = value.substr(0, pos);
            std::string val = trim(value.substr(pos));
            if (val[val.size() - 1] == ';')
                val.erase(val.size() - 1);
            if (val.empty())
            {
                std::cerr << "Error: empty error route" << std::endl;
                return (false);
            }
            char *end;
            long errorNum = strtol(key.c_str(), &end, 10);
            if (*end != '\0')
            {
                std::cerr << "Error: invalid error code" << std::endl;
                return (false);
            }
            config.errorPages[static_cast<int>(errorNum)] = val;
        }
        else if (trimmed.substr(0, 20) == "client_max_body_size")
        {
            std::string value = trim(trimmed.substr(20));
            if (value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            if (value.empty())
            {
                std::cerr << "Error: empty client max body size" << std::endl;
                return (false);
            }
            size_t multiplier = 1;
            char last = value[value.size() - 1];
            if (last == 'k' || last == 'K')
                multiplier = 1024;
            else if (last == 'm' || last == 'M')
                multiplier = 1024 * 1024;
            else if (last == 'g' || last == 'G')
                multiplier = 1024 * 1024 * 1024;
            else if (!std::isdigit(last))
            {
                std::cerr << "Error: invalid client max body size" << std::endl;
                return (false);
            }
            char *end;
            long size = strtol(value.c_str(), &end, 10);
            if ((*end != '\0' && *end != 'k' && *end != 'K' 
                && *end != 'm' && *end != 'M' && *end != 'g' && *end != 'G')
                || size < 0)
            {
                std::cerr << "Error: invalid client max body size" << std::endl;
                return (false);
            }
            config.clientMaxBodySize = static_cast<size_t>(size) * multiplier;
        }
        else if (trimmed.substr(0, 8) == "location")
        {
            std::string path = trim(trimmed.substr(8));
            if (!path.empty() && path[path.size() - 1] == '{')
                path = trim(path.substr(0, path.size() - 1));
            else if (!expectOpenBrace(file))
            {
                std::cerr << "Error: location block not opened" << std::endl;
                return (false);
            }
            if (path.empty())
            {
                std::cerr << "Error: location path is empty" << std::endl;
                return (false);
            }
            if (path[0] != '/')
            {
                std::cerr << "Error: location path must start with /" << std::endl;
                return (false);
            }
            LocationConfig loc;
            if (!loc.parseLocation(loc, file))
                return (false);
            config.locations[path] = loc;
        }
        else
        {
            std::cerr << "Error: unexpected token " << trimmed << std::endl;
            return (false); 
        }
    }
    std::cerr << "Error: location block not closed" << std::endl;
    return (false);
}

bool LocationConfig::parseLocation(LocationConfig& config, std::ifstream& file)
{
    std::string line;
    while (getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#')
            continue ;
        if (trimmed == "}" || trimmed == "};")
            return (true);
        if (trimmed.substr(0, 4) == "root")
        {
            std::string value = trim(trimmed.substr(4));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            config.root = value;
        }
        else if (trimmed.substr(0, 7) == "methods")
        {
            std::string value = trim(trimmed.substr(7));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            size_t start = 0;
            while (start <value.size())
            {
                size_t pos = value.find(' ', start);
                if (pos == std::string::npos)
                {
                    config.methods.push_back(value.substr(start));
                    break ;
                }
                config.methods.push_back(value.substr(start, pos - start));
                start = pos + 1;
            }
        }
        else if (trimmed.substr(0, 5) == "index")
        {
            std::string value = trim(trimmed.substr(5));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            config.index = value;
        }
        else if (trimmed.substr(0, 9) == "autoindex")
        {
            std::string value = trim(trimmed.substr(9));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            if (value == "off")
                config.autoindex = false;
            else if (value == "on")
                config.autoindex = true;
            else
            {
                std::cerr << "Error: invalid autoindex" << std::endl;
            }
        }
        else if (trimmed.substr(0, 12) == "upload_store")
        {
            std::string value = trim(trimmed.substr(12));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            config.uploadStore = value;
        }
        else if (trimmed.substr(0, 6) == "return")
        {
            std::string value = trim(trimmed.substr(6));
            size_t pos = value.find(' ');
            if (pos == std::string::npos)
            {
                std::cerr << "Error: invalid redirection format" << std::endl;
                return (false);
            }
            std::string error = value.substr(0, pos);
            std::string url = trim(value.substr(pos));
            if (!url.empty() && url[url.size() - 1] == ';')
                url.erase(url.size() - 1);
            config.redirect = std::make_pair(std::atoi(error.c_str()), url);
        }
        else if (trimmed.substr(0, 8) == "cgi_pass")
        {
            std::string value = trim(trimmed.substr(8));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            config.cgiPass = value;
        }
    }
    std::cerr << "Error: location block not closed" << std::endl;
    return (false);
}