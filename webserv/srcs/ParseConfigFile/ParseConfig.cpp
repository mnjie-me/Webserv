/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:42:27 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/08 14:18:31 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"
#include "LocationConfig.hpp"

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
                std::cerr << "Error: error_page has invalid format" << std::endl;
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
        else if (trimmed.substr(0, 20) == "client_max_body_size")
        {
            std::string value = trim(trimmed.substr(20));
            if (value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            if (value.empty())
            {
                std::cerr << "Error: empty client max body size" << std::endl;
                return ;
            }
            size_t multiplier = 1;
            char last = value[value.size() - 1];
            if (last == 'k' || last == 'K')
                multiplier = 1024;
            else if (last == 'm' || last == 'M')
                multiplier = 1024 * 1024;
            else if (last == 'g' || last == 'G')
                multiplier = 1024 * 1024 * 1024;
            config.clientMaxBodySize = std::atoi(value.c_str()) * multiplier;
        }
        else if (trimmed.substr(0, 8) == "location")
        {
            std::string path = trim(trimmed.substr(8));
            if (!path.empty() && path[path.size() - 1] == '{')
                path = trim(path.substr(0, path.size() - 1));
            LocationConfig loc;
            loc.parseLocation(loc, file);
            config.locations[path] = loc;
            /* std::map<std::string, LocationConfig>::iterator it;

            for (it = locations.begin(); it != locations.end(); ++it)
            {
                std::cout << "Location path: " << it->first <<  " " << it->second << std::endl;
            } */
        }
        else 
        {
            std::cerr << "Error: unexpected token " << trimmed << std::endl;
            return ;
        }
    }
}

void LocationConfig::parseLocation(LocationConfig& config, std::ifstream& file)
{
    std::string line;
    (void)config;
    //std::cout << "LOCATION" << std::endl;
    while (getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#')
            continue ;
        if (trimmed == "}" || trimmed == "};")
            return ;
        //std::cout << line << std::endl;
        if (trimmed.substr(0, 4) == "root")
        {
            std::string value = trim(trimmed.substr(4));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            config.root = value;
            //std::cout << value << std::endl;
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
                    //std::cout << config.methods.back() << std::endl;
                    break ;
                }
                config.methods.push_back(value.substr(start, pos - start));
                //std::cout << config.methods.back() << std::endl;
                start = pos + 1;
            }
        }
        else if (trimmed.substr(0, 5) == "index")
        {
            std::string value = trim(trimmed.substr(5));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            config.index = value;
            //std::cout << value << std::endl;
        }
        else if (trimmed.substr(0, 9) == "autoindex")
        {
            std::string value = trim(trimmed.substr(9));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            if (value == "off")
                config.autoindex = false;
            else
                config.autoindex = true;
        }
        else if (trimmed.substr(0, 12) == "upload_store")
        {
            std::string value = trim(trimmed.substr(12));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            config.uploadStore = value;
            //std::cout << value << std::endl;
        }
        else if (trimmed.substr(0, 6) == "return")
        {
            std::string value = trim(trimmed.substr(6));
            //std::cout << "value: [" << value << "]" << std::endl;
            size_t pos = value.find(' ');
            if (pos == std::string::npos)
            {
                std::cerr << "Error: return has invalid format" << std::endl;
                return ;
            }
            //std::cout << "pos: " << pos << std::endl;
            std::string error = value.substr(0, pos);
            std::string url = trim(value.substr(pos));
            if (!url.empty() && url[url.size() - 1] == ';')
                url.erase(url.size() - 1);
            config.redirect = std::make_pair(std::atoi(error.c_str()), url);
            //std::cout << error << " " << url << std::endl;
        }
        else if (trimmed.substr(0, 8) == "cgi_pass")
        {
            std::string value = trim(trimmed.substr(8));
            if (!value.empty() && value[value.size() - 1] == ';')
                value.erase(value.size() - 1);
            config.cgiPass = value;
            //std::cout << value << std::endl;
        }
    }
}