#include "server.hpp"


Server::Server(int port)
{
    int fd = Socket::create(port);
    Socket::setNonBlocking(fd);
    serverFds.push_back(fd); 

    pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    fds.push_back(pfd);  
}

/*Server::Server(std::vector<ServerConfig>& servers)
{
    for(size_t i = 0; i < servers.size(); i++)
    {
        int fd = Socket::create(servers[i].port);
        Socket::setNonBlocking(fd);
        serverFds.push_back(fd); 

    pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    fds.push_back(pfd);

    std::cout << "Listening on port " << servers[i].port << std::endl;
    }
}*/

bool Server::isServerFd(int fd) const
{
    for(size_t i = 0; i < serverFds.size(); i++)
        if(serverFds[i] == fd)
            return (true);
    return (false);

}

void Server::run(bool& run)
{
    while (run)
    {
        if (poll(fds.data(), fds.size(), 50000) < 0)
            continue;

        time_t now = time(NULL);
        std::vector<int> toRemove;
        for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
            if (now - it->second.getLastActivity() > 30)
                toRemove.push_back(it->first);
        }
        std::vector<int> request_read;
        std::vector<int> response_write;
        
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & (POLLERR | POLLHUP))
            {
                toRemove.push_back(fds[i].fd);
            }
            else
            {
                if (fds[i].revents & POLLIN)
                    request_read.push_back(fds[i].fd);
                if (fds[i].revents & POLLOUT)
                    response_write.push_back(fds[i].fd);
            }
            fds[i].revents = 0;
        }
        for (size_t i = 0; i < toRemove.size(); i++)
        {
            if (clients.count(toRemove[i]) > 0)
                removeClient(toRemove[i]);
        }
        for (size_t i = 0; i < request_read.size(); i++)
        {
            if (isServerFd(request_read[i]))
                acceptNewClient(request_read[i]);
            else if (clients.count(request_read[i]) > 0)
                handleClient(request_read[i]);
        }
        for (size_t i = 0; i < response_write.size(); i++)
        {
            if (clients.count(response_write[i]) > 0)
                handleResponse(response_write[i]);
        }
    }
    shutdown();
}

void Server::acceptNewClient(int serverFd)
{
    int client_fd = accept(serverFd, NULL, NULL);
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

    for (size_t i = 0; i < serverFds.size(); i++)
        Socket::close(serverFds[i]);
    serverFds.clear();
    fds.clear();
    std::cout << "Server shutdown complete." << std::endl;
}

/*   -------TO TEST!!-------

        nc localhost 8080
        GET / HTTP/1.1
        Host: localhost



        or curl -v http://localhost:8080/


        lsof -i :8080
        COMMAND     PID     USER   FD   TYPE   DEVICE SIZE/OFF NODE NAME
        a.out   1107812 iranieri    3u  IPv4 20823612      0t0  TCP *:http-alt (LISTEN)
        kill -9 1107812
*/