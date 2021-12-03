#include "../includes/irc.hpp"

/*
int main(int ac, char **av)
{
    Server *server;

    buildServer(server, av);
    return (0);
}
*/

int main(int ac, char **av)
{

    std::string str = std::string(av[1]);

    Server *server = new Server();
    Client *client = new Client();

    /*** SET NOS VARAIBLES POUR LES TESTS ***/
    server->set_name("testing.com");
    client->set_hostname(server->get_name());
    client->set_nickname("foo_nick");

    /***EXECUTION ***/
    client->set_unparsed_client_command(str);
    client->store_prefix();
    client->store_command();
    client->store_params();

#if DEBUG
    client->display_command();
#endif

    client->_server = server;
    //TODO //client->check_command();
    client->exec_command();

    delete client;
    delete server;
}