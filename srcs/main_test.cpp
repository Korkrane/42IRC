#include <irc.hpp>
/**
 * @brief Precedemmen utilisee pour tester le parsing avant que la partie
 * network soit terminee
 * 
 * @param port 
 * @param password 
 * @param server 
 * @param str 
 * @return int 
 */
int test_parsing(std::string port, std::string password, Server *server, std::string str)
{
    Client *client = new Client();

    /*** SET NOS VARAIBLES POUR LES TESTS ***/
    server->set_name("testing.com");
    client->set_hostname(server->get_name());
    client->set_nickname("foo_nick");

    /***EXECUTION ***/
    client->set_unparsed_client_command(str);
    //std::cout << "1. " << client->get_unparsed_client_command() << std::endl;
    client->store_prefix();
    //std::cout << "2. " << client->get_prefix() << std::endl;
    client->store_command();
    std::cout << "3. " << client->get_command_name() << std::endl;
    client->store_params();
    //std::cout << "4. Printing params: " << std::endl;
    client->display_params();

#if DEBUG
    client->display_command();
#endif

    client->_server = server;
    //TODO //client->check_command();
    client->exec_command();

    delete client;
    return (0);
}

/**
 * @brief Get the port object
 * 
 * @param first_arg 
 * @return std::string 
 * TODO: checker qu il s'agit bien d'un port (reprendre atoi strict)
 */
std::string get_port(char *first_arg)
{
    //on convertie d'abord le char * en string
    (void)first_arg;
    std::string port;

    port.assign(first_arg);
#if DEBUG
    std::cout << "Port string is " << port << std::endl;
#endif
    //The RFC 6m056 says that the range for ephemeral ports should be 1024–65535
    //On check si ca correspond a un port
    int port_number = std::stoi(port);
#if DEBUG
 //   std::cout << "Port number is " << port_number << std::endl;
#endif
    //On retourne une string vide si le port number est incorrect
    if (port_number < 1024  || port_number > 65535)
        return (std::string());
    return (port);
}

/**
 * @brief Get the password object
 * 
 * @param second_arg 
 * @return std::string 
 * TODO: checker si exigeances sur le password
 */
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
    //Doivent faire partie des args
    ///ajouter des checks 
    std::string port;
    std::string password;
    (void)port;
    (void)password;
    /*
    ** Voir host
    ** Port network
    ** passqork network
    */
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
        //Ces fonctions vont permettre de verifier que les arguments respectent bien la syntaxe attendue
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
    //Construction du server 
    //TODO: ajouter ce constructeur ?
    //Server serv(port, password);

   // Server *server;
    //buildServer(server, av);
    //delete server;
   //TESTS PARSING 
   // std::string str = std::string(av[1]);
   // Server *server = new Server();
   //test_parsing(port, password, server, str);
    //delete server;
}