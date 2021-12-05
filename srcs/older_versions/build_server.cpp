#include <irc.hpp>


/**
 * @brief Set the server time creation
 *
 * @param server
 */
void setServerTime(Server *server)
{
    time_t      now    = time(0);
    std::string date   = ctime(&now);

    server->set_creation(date, now);
}

/**
 * @brief Set the server socket, bind it to a port and set it to listen
 *
 * @param server
 */
void setServerSocket(Server *server)
{
#ifdef DEBUG
    std::cout << "\n-- Server socket setting ---" << std::endl;
#endif
    int                sockfd;
    struct sockaddr_in addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        throw SocketCreationFailed();

    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) // https://stackoverflow.com/questions/24194961/how-do-i-use-setsockoptso-reuseaddr
        throw SocketCreationFailed();

#ifdef DEBUG
    std::cout << "Server Socket built is successful" << std::endl;
#endif

    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(server->get_port());
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        throw SocketBindingFailed();

#ifdef DEBUG
    std::cout << "Server Socket bind is successful, port: " << server->get_port() << std::endl;
#endif

    if (listen(sockfd, 10) < 0)
        throw SocketListeningFailed();

#ifdef DEBUG
    std::cout << "Server listening for connection on port: " << server->get_port() << std::endl;
#endif
}

void setServerDefault(Server *server, char **av)
{
    server->set_port(atoi(av[1]));
    server->set_password(std::string(av[2]));
}

void buildServer(Server *server, char **av)
{
    server = new Server();

    try
    {
        setServerDefault(server, av);
        setServerTime(server);
        setServerSocket(server);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        delete server;
    }
}