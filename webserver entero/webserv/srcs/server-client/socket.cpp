#include "socket.hpp"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstring>
#include <stdexcept>
#include <unistd.h>
#include <errno.h>

int Socket::create(int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        throw std::runtime_error("socket failed");

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        throw std::runtime_error("setsockopt failed");

    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    std::cout << addr.sin_family << std::endl;
std::cout << "Puerto: " << ntohs(addr.sin_port) << std::endl;
    std::cout << addr.sin_addr.s_addr << std::endl;

    if (bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0)
       //throw std::runtime_error("bind failed");
    throw std::runtime_error(std::string("bind failed: ") + strerror(errno));

    if (listen(fd, 10) < 0)
        throw std::runtime_error("listen failed");

    return fd;
}

void Socket::setNonBlocking(int fd)
{
    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("fcntl failed");
}

void Socket::close(int fd)
{
    ::close(fd);
}