#ifndef SOCKET_HPP
#define SOCKET_HPP

class Socket
{
    public:
        static int  create(int port);
        static void setNonBlocking(int fd);
        static void close(int fd);
};

#endif
