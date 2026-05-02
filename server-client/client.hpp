#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <netinet/in.h>

#include "ServerConfig.hpp"


class Client 
{
private:
    int fd;
    ServerConfig config;
    std::string readBuffer;
    std::string writeBuffer;
    sockaddr_in addr;
    time_t lastActivity;

public:
    bool        shouldClose;
    Client();
    Client(int fd, const ServerConfig& config);
    Client(const Client& other);             
    Client& operator=(const Client& other);
    ~Client();
    ServerConfig& getConfig();

    int getFd() const;
    std::string& getBuffer();
    ssize_t readData(); 
    time_t getLastActivity() const;

    bool    isRequestComplete() const;
    void    resetBuffer();

    void    appendToSendBuffer(const std::string& data);
    ssize_t drainSendBuffer();
    bool    hasPendingData() const;
};

#endif