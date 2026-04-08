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
    int                     server_fd;
    std::vector<pollfd>     fds;
    std::map<int, Client>   clients;

    void acceptNewClient();
    void handleClient(int fd);
    void removeClient(int fd);
    void handleWrite(int fd);

public:
    Server(int port);
    void run();
    void shutdown();

};

#endif