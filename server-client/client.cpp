#include "client.hpp"
#include <unistd.h>
#include <sys/socket.h>
#include <ctime>

Client::Client() : fd(-1), shouldClose(false), lastActivity(time(NULL))  {}

Client::Client(int fd) : fd(fd), shouldClose(false), lastActivity(time(NULL)) {}

int Client::getFd() const
{
    return fd;
}

std::string& Client::getBuffer()
{
    return readBuffer;
}

ssize_t Client::readData()
{
    char temp[1024];
    ssize_t bytes = read(fd, temp, sizeof(temp));
    if (bytes > 0)
    {
        readBuffer.append(temp, bytes);
        lastActivity = time(NULL);  
    }
    return bytes;
}

bool Client::isRequestComplete() const
{
    return (readBuffer.find("\r\n\r\n") != std::string::npos);
}

void Client::resetBuffer()
{
    readBuffer.clear();
}

time_t Client::getLastActivity() const
{
    return lastActivity;
}

void Client::appendToSendBuffer(const std::string& data)
{
    writeBuffer.append(data);
}

ssize_t Client::drainSendBuffer()
{
    if (writeBuffer.empty()) 
    {
        return 0;
    }
    ssize_t bytes = send(fd, writeBuffer.c_str(), writeBuffer.size(), 0);
    if (bytes > 0)
        writeBuffer.erase(0, bytes);
    return bytes;
}

bool Client::hasPendingData() const
{
    return !writeBuffer.empty();
}


/*echo -e "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n" | nc localhost 8080*/