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

public:
    bool        shouldClose;
    Client();
    Client(int fd);

    int getFd() const;
    std::string& getBuffer();
    ssize_t readData();
    bool    isRequestComplete() const;
    void    resetBuffer();

    void    appendToSendBuffer(const std::string& data);
    ssize_t drainSendBuffer();
    bool    hasPendingData() const;
};

#endif