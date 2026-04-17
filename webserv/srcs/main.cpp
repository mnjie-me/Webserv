/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:50:08 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/17 14:19:25 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerConfig.hpp"
#include "Router.hpp"
#include "Method.hpp"

int main(int ac, char **av)
{
    Request input;
    ServerConfig config;
    std::vector<ServerConfig> servers;
    Router  route;
    Method method;

    if (ac == 2)
    {
        config.parseConfigFile(av[1], servers);
        input.parseRequest("POS /cgi-bin/script.php HTTP/1.1\r\nHost: localhost\r\n\r\n", servers[0]);
/*         if (input.getError() != 0)
        {
            std::cout << "Error: " << input.getError() << std::endl;
        } 
        else
        {*/
            route.handleRequest(input, servers[0]);
            method.executeMethod(input, route);
 //       }
    }
    return (0);    
}


// Test extra characters on input
// echo -e | ./Webserv | cat -A