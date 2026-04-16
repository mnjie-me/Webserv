#include "server.hpp"


Server::Server(int port)
{
    server_fd = Socket::create(port);

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
        if (poll(fds.data(), fds.size(), 5000) < 0)
            continue;

        time_t now = time(NULL);
        std::vector<int> toRemove;
        for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
            if (now - it->second.getLastActivity() > 30)
                toRemove.push_back(it->first);
        }
        std::vector<int> request;
        std::vector<int> response;
        
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & (POLLERR | POLLHUP))
            {
                toRemove.push_back(fds[i].fd);
            }
            else
            {
                if (fds[i].revents & POLLIN)
                    request.push_back(fds[i].fd);
                if (fds[i].revents & POLLOUT)
                    response.push_back(fds[i].fd);
            }
            fds[i].revents = 0;
        }
        for (size_t i = 0; i < toRemove.size(); i++)
        {
            if (clients.count(toRemove[i]) > 0)
                removeClient(toRemove[i]);
        }
        for (size_t i = 0; i < request.size(); i++)
        {
            if (request[i] == server_fd)
                acceptNewClient();
            else if (clients.count(request[i]) > 0)
                handleClient(request[i]);
        }
        for (size_t i = 0; i < response.size(); i++)
        {
            if (clients.count(response[i]) > 0)
                handleResponse(response[i]);
        }
    }
}

void Server::acceptNewClient()
{
    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0)
        return;

    Socket::setNonBlocking(client_fd);

    pollfd pfd;
    pfd.fd = client_fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    fds.push_back(pfd);

    clients[client_fd] = Client(client_fd);
    std::cout << "New client connected: " << client_fd << std::endl;
}

void Server::handleResponse(int fd)
{
    Client& client = clients[fd];
    
    ssize_t sent = client.drainSendBuffer();
    if (sent < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return;
        removeClient(fd);
        return;
    }

    if (!client.hasPendingData())
    {
        if (client.shouldClose)
        {
            removeClient(fd);
            return;
        }
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].fd == fd)
            {
                fds[i].events = POLLIN;
                break;
            }
        }
    }
}


void Server::handleClient(int fd)
{
    ssize_t bytes = clients[fd].readData();

    
    if (bytes == 0)
    {
        removeClient(fd);
        return;
    }
    if (bytes < 0)  
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return;  
        removeClient(fd);
        return;
    }

    if (clients[fd].isRequestComplete())
    {
        std::string buffer = clients[fd].getBuffer();
        bool shouldClose = (buffer.find("Connection: close") != std::string::npos);

        std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nHello";
        clients[fd].appendToSendBuffer(response);
        clients[fd].shouldClose = shouldClose;  
        clients[fd].resetBuffer();
        
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].fd == fd)
            {
                fds[i].events = POLLIN | POLLOUT;
                break;
            }
        }
    }
}

void Server::removeClient(int fd)
{
    Socket::close(fd);
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
    for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        std::cout << "Closing client: " << it->first << std::endl;
        Socket::close(it->first);
    }
    clients.clear();

    if (server_fd >= 0)
    {
        Socket::close(server_fd);
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