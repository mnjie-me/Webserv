#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <netinet/in.h>


class Client 
{
private:
    int fd;
    std::string readBuffer;
    std::string writeBuffer;
    sockaddr_in addr;
    time_t lastActivity;

public:
    bool        shouldClose;
    Client();
    Client(int fd);

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