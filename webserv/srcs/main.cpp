/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:50:08 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/26 13:49:33 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerConfig.hpp"
#include "Router.hpp"
#include "Method.hpp"

int main(int ac, char **av)
{
    
    if (ac == 2)
    {
        Request input;
        ServerConfig config;
        std::vector<ServerConfig> servers;
        Router  route;
        Method method;
        config.parseConfigFile(av[1], servers);
        if (servers.empty())
        {
            std::cerr << "Error: no servers configured" << std::endl;
            return (1);
        }
        input.parseRequest("POST /upload HTTP/1.1\r\nHost: localhost\r\nContent-Length: 13\r\n\r\nHello, World!", servers[0]);        route.handleRequest(input, servers[0]);
        Response response = method.executeMethod(input, route);
        /* std::cerr << "status: " << response.getStatusCode() << std::endl;
        std::cerr << "body: " << response.getBody() << std::endl; */
    }
    else
    {
        std::cerr << "Error: missing congigure file" << std::endl;
    }
    return (0);    
}