#include <irc.hpp>

//Appel fonction qui va appeler les 4 commandes necessaires a la client/user registration ?

void Commands::welcome_cmd(User *user, IRC *server)
{
    (void)user;
    (void)server;

    std::vector<std::string> reply_params;
    std::string              reply;

    //reply 1
    reply_params.push_back(user->get_nickname());
    reply_params.push_back(user->get_username());
    reply_params.push_back(user->get_hostname());
    reply = build_reply(1, user, reply_params);
    server->responseQueue.push_back(std::make_pair(user->get_socket(), reply));
    reply_params.clear();

    //reply 2
    reply_params.push_back(user->get_hostname());
    reply = build_reply(2, user, reply_params);
    server->responseQueue.push_back(std::make_pair(user->get_socket(), reply));
    reply_params.clear();

    //reply 3
    reply_params.push_back(server->get_server_creation());
    reply = build_reply(3, user, reply_params);
    server->responseQueue.push_back(std::make_pair(user->get_socket(), reply));
    reply_params.clear();

    //reply 4
    reply_params.push_back(user->get_hostname());
    reply = build_reply(4, user, reply_params);
    server->responseQueue.push_back(std::make_pair(user->get_socket(), reply));
    reply_params.clear();

   server->_commands->motd_cmd(user, server);
}