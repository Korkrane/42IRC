#include <IRC.hpp>

void Commands::welcome_cmd(User *user, IRC *server)
{
    std::vector<std::string> params;

    //reply 1
    params.push_back(user->get_nickname());
    params.push_back(user->get_username());
    params.push_back(user->get_hostname());
    server->send_rpl("001", user, params, "");
    params.clear();

    //reply 2
    params.push_back(user->get_hostname());
    server->send_rpl("002", user, params, "");
    params.clear();

    //reply 3
    params.push_back(server->get_server_creation());
    server->send_rpl("003", user, params, "");
    params.clear();

    //reply 4
    params.push_back(user->get_hostname());
    server->send_rpl("004", user, params, "");
    params.clear();

   server->_commands->motd_cmd(user, server);
}