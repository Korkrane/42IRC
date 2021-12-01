#include "../includes/irc.hpp"

int main(int ac, char **av)
{
    Server *server;

    buildServer(server, av);
    return (0);
}