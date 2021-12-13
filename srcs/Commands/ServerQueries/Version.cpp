#include <IRC.hpp>

void Commands::version_cmd(User *user, IRC *server)
{
    std::vector<std::string> params;

    if (user->get_params().empty() || (user->get_params()[0] == server->get_name()))
    {
        // TODO check for degublevel & comments (hardcoded atm)
        params.push_back(server->get_version());
        params.push_back("debuglevel00");
        params.push_back(server->get_name());
        params.push_back("random comments as test");
        server->send_rpl("351", user, params, "");
    }
    else if (!user->get_params().empty() && user->get_params()[0] != server->get_name())
    {
        params.push_back(user->get_params()[0]);
        server->send_rpl("402", user, params, "");
    }
}