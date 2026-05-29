/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:50:08 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/05/29 16:37:37 by mnjie-me         ###   ########.fr       */
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

        if (!config.parseConfigFile(av[1], servers))
            return (1);
        if (servers.empty())
        {
            std::cerr << "Error: no servers configured" << std::endl;
            return (1);
        }
        Server server(servers);
        server.run(g_running);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return (1);
    }

    return (0);    
}