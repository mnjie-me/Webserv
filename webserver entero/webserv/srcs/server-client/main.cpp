/* #include "server.hpp"
#include "ServerConfig.hpp"
#include <csignal>
#include <iostream>
#include <vector>

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
        // Creamos el config manualmente sin parsear archivo
        ServerConfig config;
        config.port = 8080;
        config.serverName = "localhost";

        std::vector<ServerConfig> servers;
        servers.push_back(config);

        Server server(servers);
        server.run(g_running);
    }
    catch (std::exception& e)
    {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} */