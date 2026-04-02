#include "client.hpp"
#include <unistd.h>


Client::Client() : fd(-1) {}

Client::Client(int fd) : fd(fd) {}

int Client::getFd() const
{
    return fd;
}

std::string& Client::getBuffer()
{
    return buffer;
}

ssize_t Client::readData()
{
    char temp[1024];

    ssize_t bytes = read(fd, temp, sizeof(temp));  

    if (bytes > 0)
        buffer.append(temp, bytes);

    return bytes;  
}

bool Client::isRequestComplete() const
{
    return (buffer.find("\r\n\r\n") != std::string::npos);
}

void Client::resetBuffer()
{
    buffer.clear();
}


/*echo -e "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n" | nc localhost 8080*/