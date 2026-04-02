#include "server.hpp"

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

Server::Server(int port)
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
        throw std::runtime_error("socket failed");

    int opt = 1;
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        throw std::runtime_error("setsockopt failed");

    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("bind failed");

    listen(server_fd, 10);

    pollfd pfd;
    pfd.fd = server_fd;
    pfd.events = POLLIN;
    pfd.revents = 0;

    fds.push_back(pfd);
}

void Server::run()
{
    while (true)
    {
        if (poll(fds.data(), fds.size(), -1) < 0)
            continue;

        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLIN)
            {
                int current_fd = fds[i].fd;

                if (current_fd == server_fd)
                    acceptNewClient();
                else
                {
                    handleClient(current_fd);
                    break; 
                }
            }
            fds[i].revents = 0;
        }
    }
}

void Server::acceptNewClient()
{
    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0)
        return;

    pollfd pfd;
    pfd.fd = client_fd;
    pfd.events = POLLIN;
    pfd.revents = 0;

    fds.push_back(pfd);
    clients[client_fd] = Client(client_fd);

    std::cout << "New client connected: " << client_fd << std::endl;
}

std::string handle_request(const std::string& request)
{
    (void)request;
    return "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nHello";
}


void Server::handleClient(int fd)
{
    ssize_t bytes = clients[fd].readData();

    if (bytes <= 0)
    {
        removeClient(fd);
        return;
    }

    if (clients[fd].isRequestComplete())
    {
        std::cout << "Request from client " << fd << ":\n"
                  << clients[fd].getBuffer() << std::endl;

        
        std::string response = handle_request(clients[fd].getBuffer());

        write(fd, response.c_str(), response.size());

        std::cout << "Response sent to client " << fd << ":\n"
                  << response << std::endl;

        std::string buffer = clients[fd].getBuffer();
        bool shouldClose = (buffer.find("Connection: close") != std::string::npos);

        if (shouldClose)
        {
            std::cout << "Closing client due to Connection: close: " << fd << std::endl;
            removeClient(fd);
        }
        else
        {
            clients[fd].resetBuffer();
        }
    }
}

void Server::removeClient(int fd)
{
    close(fd);
    clients.erase(fd);

    for (size_t i = 0; i < fds.size(); i++)
    {
        if (fds[i].fd == fd)
        {
            fds.erase(fds.begin() + i);
            break;
        }
    }

    std::cout << "Client disconnected: " << fd << std::endl;
}
void Server::shutdown()
{
    
   for (auto& pair : clients)
        {
            int fd = pair.first;
            std::cout << "Closing client: " << fd << std::endl;
            close(fd);
        }
        clients.clear();

        
        if (server_fd >= 0)
        {
            std::cout <<  std::endl;
            std::cout << "Closing server socket: " << server_fd << std::endl;
            close(server_fd);
            server_fd = -1;
        }

        
        fds.clear();

        std::cout << "Server shutdown complete." << std::endl;
}

/*   -------TO TEST!!-------

        nc localhost 8080
        GET / HTTP/1.1
        Host: localhost

*/