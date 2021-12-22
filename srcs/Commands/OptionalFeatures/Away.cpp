#include "IRC.hpp"

void Commands::away_cmd(User *user, IRC *server)
{
    std::vector<std::string> reply_params;
    std::vector<std::string> params = user->get_params();

    if (user->is_away() && params.empty())
    {
        user->is_away(false);
        user->set_away_mssg("");
        server->send_rpl("305", user, reply_params, "");
    }
    else
    {
        user->is_away(true);
        if (!params.empty())
            user->set_away_mssg(params[0]);
        server->send_rpl("306", user, reply_params, "");
    }
}