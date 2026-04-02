#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <iostream>
#include <string>
#include <cstring>      

#include <unistd.h>     
#include <fcntl.h>      

#include <sys/types.h>
#include <sys/socket.h> 

#include <netinet/in.h> 
#include <arpa/inet.h>  

#include <poll.h>
#include <map> 
#include "client.hpp"  


class Server 
{
    private: 
        int server_fd;
        std::vector<pollfd> fds;
        std::map<int, Client> clients;

        void acceptNewClient();
        void handleClient(int fd);
        void removeClient(int fd);
        


    public:
        Server (int port);

      //  ~Server();

      //  void init();
        void run();
        void shutdown();
};

#endif


