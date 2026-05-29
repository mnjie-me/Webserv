/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:50:08 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/05/27 19:40:56 by iranieri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerConfig.hpp"
#include "Router.hpp"
#include "Method.hpp"
#include "server.hpp"
#include "ServerConfig.hpp"
#include "client.hpp"
#include <csignal>
#include <iostream>
#include <vector>

static bool g_running = true;

void signal_handler(int signum)
{
    (void)signum;
    g_running = false;
}

/* int main()
{
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    try
    {
        // Creamos el config manualmente sin parsear archivo
        ServerConfig config;
        config.port = 8080;
        config.serverName = "localhost";

        std::vector<ServerConfig> servers;
        servers.push_back(config);

        Server server(servers);
        server.run(g_running);
    }
    catch (std::exception& e)
    {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} */

int main(int ac, char **av)

{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " <config_file>" << std::endl;
        return (1);
    }

    try
    {
        Request input;
        ServerConfig config;
        std::vector<ServerConfig> servers;
        Router  route;
        Method method;
        
        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);

        // crear un if con el resultado booleano de la función
        config.parseConfigFile(av[1], servers);
        if (servers.empty())
        {
            std::cerr << "Error: no servers configured" << std::endl;
            return (1);
        }
        //servers.push_back(config);
        Server server(servers);
        server.run(g_running);
        
        /* Client client;
        unsigned long i = 0;
        while (i < servers.size())
        {
            input.parseRequest(client.getBuffer(), servers[i]);
            route.handleRequest(input, servers[0]);
            Response response = method.executeMethod(input, route);
            i++;
        }
        return (0); */
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return (1);
    }

    return (0);    
}
