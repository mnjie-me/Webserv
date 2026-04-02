
#include "server.hpp"
#include <csignal> 
#include <cstdlib>

Server* globalServer = nullptr;   

void signal_handler(int signum)
{
    if (globalServer)
        globalServer->shutdown(); 
    std::exit(0);                 
}
int main()
{
    Server server(8080);
    globalServer = &server;

    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    server.run();
    return 0;
}
