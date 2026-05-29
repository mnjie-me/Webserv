/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 14:18:32 by mnjie-me          #+#    #+#             */
/*   Updated: 2026/05/29 14:18:34 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <map>
#include <iostream>
#include <string>

#include <poll.h>
#include "ServerConfig.hpp"
#include "socket.hpp"
#include "client.hpp"

class Server
{
private:
    std::map<int, std::vector<ServerConfig> > serverMap;
    std::map<int, Client>   clients;
    std::vector<pollfd>     fds;

    void acceptNewClient(int serverFd);
    void handleClient(int fd);
    void removeClient(int fd);
    void handleResponse(int fd);
    bool isServerFd(int fd) const;

public:
    Server(std::vector<ServerConfig>& servers);
    Server(const Server& other);
    Server& operator=(const Server& other);
    void run(bool& running);
    void shutdown();
    ~Server();
};

#endif