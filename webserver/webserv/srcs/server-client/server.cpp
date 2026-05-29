#include "server.hpp"
#include "Request.hpp"
#include "ServerConfig.hpp"
#include "Router.hpp"
#include "Method.hpp"
#include "server.hpp"
#include "ServerConfig.hpp"
#include "client.hpp"
#include "Response.hpp"

Server::Server(std::vector<ServerConfig>& servers)
{
    for(size_t i = 0; i < servers.size(); i++)
    {
        int fd = Socket::create(servers[i].port);
        Socket::setNonBlocking(fd);
        serverMap[fd] = servers[i]; 

        pollfd pfd;
        pfd.fd = fd;
        pfd.events = POLLIN;
        pfd.revents = 0;
        fds.push_back(pfd);

        std::cout << "Listening on port " << servers[i].port << std::endl;
    }
}

Server::Server(const Server& other)
    : serverMap(other.serverMap),
      clients(other.clients),
      fds(other.fds)
{}

Server& Server::operator=(const Server& other)
{
    if (this != &other)
    {
        serverMap = other.serverMap;
        clients = other.clients;
        fds = other.fds;
    }
    return *this;
}

bool Server::isServerFd(int fd) const
{
    return (serverMap.count(fd) > 0);
}

void Server::run(bool& run)
{
    while (run)
    {
        int ret = poll(fds.data(), fds.size(), 1000);

        if (ret < 0)
            continue;
        if (ret == 0) 
            continue;
        time_t now = time(NULL);
        std::vector<int> toRemove;
        std::vector<int> readyServerFds;
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
            if (fds[i].revents & POLLIN)
            {
                if (isServerFd(fds[i].fd))
                {
                    readyServerFds.push_back(fds[i].fd);
                }
                else
                {
                    request_read.push_back(fds[i].fd); 
                }
            }

            if (fds[i].revents & POLLOUT)
            {
                response_write.push_back(fds[i].fd);
            }
            fds[i].revents = 0;
        }
        for (size_t i = 0; i < readyServerFds.size(); i++)
            acceptNewClient(readyServerFds[i]);

        for (size_t i = 0; i < request_read.size(); i++)
        {
            if (clients.count(request_read[i]) > 0)
                handleClient(request_read[i]);
        }
        for (size_t i = 0; i < response_write.size(); i++)
        {
            if (clients.count(response_write[i]) > 0)
                handleResponse(response_write[i]);
        }                                    
        for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
            int fd = it->first;
            Client& client = it->second;
            
            for (size_t i = 0; i < fds.size(); i++)
            {
                if (fds[i].fd == fd)
                {
                    if (client.hasPendingData())
                        fds[i].events = POLLIN | POLLOUT;
                    else
                        fds[i].events = POLLIN;
                    break;
                }
            }
        }
        for (size_t i = 0; i < toRemove.size(); i++)
        {
            if (clients.count(toRemove[i]) > 0)
                removeClient(toRemove[i]);
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

    clients[client_fd] = Client(client_fd, serverMap[serverFd]);

    std::cout << "New client connected: " << client_fd << std::endl;
}

void Server::handleResponse(int fd)
{
    if (clients.count(fd) == 0) return;
        Client& client = clients[fd];
    
    ssize_t sent = client.drainSendBuffer();
    if (sent == -1)
    {
        removeClient(fd);
        return;
    }
    if (sent <0)
    {
        removeClient(fd);
        return;
    }

    if (client.hasPendingData())
        return;
    
    std::cout << "Response sent to client: " << fd << std::endl;

    if(client.shouldClose)
    {
        removeClient(fd);
        return;
    }
}


void Server::handleClient(int fd)
{
    if (clients.count(fd) == 0)
        return;
    
    Client& client = clients[fd];
    ServerConfig& config = client.getConfig();    

    ssize_t bytes = clients[fd].readData();
    std::cout << "[READ] fd=" << fd << " bytes=" << bytes << std::endl;

    if (bytes == 0)
    {
        removeClient(fd);
        return;
    }
    if (bytes == -1)  
    {
        removeClient(fd);
        return;
    }

    if (client.isRequestComplete())
    {
        std::string buffer = client.getBuffer();

        bool shouldClose = (buffer.find("Connection: close") != std::string::npos);

        std::string firstLine = buffer.substr(0, buffer.find("\r\n"));
        std::cout << "Request  fd=" << fd << " [" << firstLine << "]" << std::endl;
        Router  route;
        Method method;
        Request input;
        input.parseRequest(client.getBuffer(), config);
        route.handleRequest(input, config);
        Response response = method.executeMethod(input, route);
        std::cerr << "status: " << response.getStatusCode() << std::endl;
        client.appendToSendBuffer(response.toString());
        client.shouldClose = shouldClose;  
        client.resetBuffer();
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

    for (std::map<int, ServerConfig>::iterator it = serverMap.begin(); it != serverMap.end(); ++it)
    {
        Socket::close(it->first);
    }
    serverMap.clear();
    fds.clear();
    std::cout << "Server shutdown complete." << std::endl;
}
Server::~Server()
{
    shutdown();
}
