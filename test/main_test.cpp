#include <irc.hpp>

//Parsing 
/*
int test_parsing(std::string port, std::string password, Server *server, std::string str)
{
    Client *client = new Client();

    //SET NOS VARAIBLES POUR LES TESTS
    server->set_name("testing.com");
    client->set_hostname(server->get_name());
    client->set_nickname("foo_nick");

    client->set_unparsed_client_command(str);
    client->store_prefix();
    client->store_command();
    std::cout << "3. " << client->get_command_name() << std::endl;
    client->store_params();
    client->display_params();
    client->_server = server;
    client->exec_command();

    delete client;
    return (0);
}

std::string get_port(char *first_arg)
{
    (void)first_arg;
    std::string port;

    port.assign(first_arg);
    int port_number = std::stoi(port);
    if (port_number < 1024  || port_number > 65535)
        return (std::string());
    return (port);
}

std::string get_password(char *second_arg)
{
    (void)second_arg;
    std::string password;

    password.assign(second_arg);
#if DEBUG
    std::cout << "Argument password is " << password << std::endl;
#endif
    return (password);
}

int main(int ac, char **av)
{
    std::string port;
    std::string password;
    (void)port;
    (void)password;
#if DEBUG
    std::cout << "There are " << ac << " argument(s)" << std::endl;
#endif
    if (ac != 3)
    {
        std::cout << "Error: Wrong number of arguments." << std::endl;
        exit (1);
    }
    else
    {
        port = get_port(av[1]);
        if (port.empty())
        {
            std::cout << "Error: incorrect port argument." << std::endl;
            exit (1);
        }
        password = get_password(av[2]);
        if (password.empty())
        {
            std::cout << "Error: incorrect password argument" << std::endl;
            exit (1);
        }
    }
}
*/