/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:50:08 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/03/30 21:45:14 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int main()
{
    Request input;

    input.parseRequest("GET /index.html HTTP/1.1\r\nHost: localhost\r\n \r\n");
}


// Test extra characters on input
// echo -e | ./Webserv | cat -A