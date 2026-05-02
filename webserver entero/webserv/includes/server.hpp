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
    std::map<int, ServerConfig> serverMap;
    std::map<int, Client>   clients;
    std::vector<pollfd>     fds;

    void acceptNewClient(int serverFd);
    void handleClient(int fd, std::vector<ServerConfig> servers);
    void removeClient(int fd);
    void handleResponse(int fd);
    bool isServerFd(int fd) const;

public:
    Server(std::vector<ServerConfig>& servers);
    Server(const Server& other);
    Server& operator=(const Server& other);
    void run(bool& running, std::vector<ServerConfig> servers);
    void shutdown();
    ~Server();
};

#endif