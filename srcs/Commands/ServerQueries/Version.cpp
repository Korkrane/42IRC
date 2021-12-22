#include "IRC.hpp"

void Commands::version_cmd(User *user, IRC *server)
{
    std::vector<std::string> reply_params;

    if (user->get_params().empty() || (user->get_params()[0] == server->get_name()))
    {
        // TODO check for degublevel & comments (hardcoded atm)
        reply_params.push_back(server->get_version());
        reply_params.push_back("debuglevel00");
        reply_params.push_back(server->get_name());
        reply_params.push_back("random comments as test");
        server->send_rpl("351", user, reply_params, "");
    }
    else if (!user->get_params().empty() && user->get_params()[0] != server->get_name())
    {
        reply_params.push_back(user->get_params()[0]);
        server->send_rpl("402", user, reply_params, "");
    }
}