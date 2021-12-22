#include "IRC.hpp"

void Commands::unknown_cmd(User *user, IRC *server)
{
    std::vector<std::string> reply_params;

    reply_params.push_back(user->get_command_name());
    server->send_rpl("421", user, reply_params, "");
}