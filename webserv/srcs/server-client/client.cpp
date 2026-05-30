#include "client.hpp"
#include <unistd.h>
#include <sys/socket.h>
#include <ctime>

Client::Client() : fd(-1), lastActivity(time(NULL)), shouldClose(false)  {}

Client::Client(int fd, const ServerConfig& config) : fd(fd), config(config), lastActivity(time(NULL)), shouldClose(false) {}

Client::Client(const Client& other) 
    : fd(other.fd), config(other.config), readBuffer(other.readBuffer),
      writeBuffer(other.writeBuffer), addr(other.addr), 
      lastActivity(other.lastActivity), shouldClose(other.shouldClose)
{}

Client& Client::operator=(const Client& other)
{
    if (this != &other)
    {
        fd = other.fd;
        config = other.config;
        readBuffer = other.readBuffer;
        writeBuffer = other.writeBuffer;
        addr = other.addr;
        lastActivity = other.lastActivity;
        shouldClose = other.shouldClose;
    }
    return *this;
}

Client::~Client() {}

ServerConfig& Client::getConfig()
{
    return config;
}

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
    if(fd <0)
        return -1;
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
    size_t pos = readBuffer.find("\r\n\r\n");
    if (pos == std::string::npos)
        pos = readBuffer.find("\n\n");
    if (pos == std::string::npos)
        return (false);
    size_t clPos = readBuffer.find("Content-Length: ");
    if (clPos == std::string::npos)
        return (true);
    size_t valueStart = clPos + 16;
    size_t valueEnd = readBuffer.find("\r\n", valueStart);
    std::string clValue = readBuffer.substr(valueStart, valueEnd - valueStart);
    size_t contentLength = std::atoi(clValue.c_str());
    size_t headerEnd = pos + 4;
    size_t bodyReceived = readBuffer.size() - headerEnd;
    return (bodyReceived >= contentLength);
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
    if (fd < 0 || writeBuffer.empty()) 
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

