/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:50:08 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/04/07 13:00:43 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerConfig.hpp"

int main(int ac, char **av)
{
    Request input;
    ServerConfig config;

    if (ac == 2)
    {
        config.parseConfigFile(av[1]);
        input.parseRequest("GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n", config);
        if (input.getError() != 0)
        {
            std::cout << "Error: " << input.getError() << std::endl;
        }
    }
    return (0);    
}


// Test extra characters on input
// echo -e | ./Webserv | cat -A