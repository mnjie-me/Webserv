
#include "server.hpp"
#include <csignal> 
#include <cstdlib>

#include "server.hpp"
#include <csignal>
#include <iostream>

static bool g_running = true;

void signal_handler(int signum)
{
    (void)signum;
    g_running = false;
}

int main()
{
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    try
    {
        Server server(8080);
        server.run(g_running);
    }
    catch (std::exception& e)
    {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
