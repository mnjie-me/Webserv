#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <map>
#include <iostream>
#include <string>

#include <poll.h>

#include "socket.hpp"
#include "client.hpp"

class Server
{
private:
    std::vector<int> serverFds;
    std::vector<pollfd>     fds;
    std::map<int, Client>   clients;

    void acceptNewClient(int serverFd);
    void handleClient(int fd);
    void removeClient(int fd);
    void handleResponse(int fd);
    bool isServerFd(int fd) const;

public:
    Server(int port); // TO REMOVE LATER!!!!!!!

    // Server(std::vector<ServerConfig>& servers);
    void run(bool& running);
    void shutdown();

};

#endif