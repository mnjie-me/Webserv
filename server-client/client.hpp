#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <netinet/in.h>


class Client 
{
private:
    int fd;
    std::string buffer;
    sockaddr_in addr;

public:
    Client();
    Client(int fd);

    int getFd() const;
    std::string& getBuffer();

    ssize_t readData();
    bool isRequestComplete() const;

    void resetBuffer();
};

#endif