#include <IRC.hpp>

void Commands::away_cmd(User *user, IRC *server) // 305 & 306 reply
{
    std::vector<std::string> reply_params;
    std::vector<std::string> user_params = user->get_params();

    if (user->is_away() && user_params.empty()) // s'il est deja afk mais pas de param on le marque non afk
    {
        user->is_away(false);
        user->set_away_mssg("");
        server->send_rpl("305", user, reply_params, "");
    }
    else
    {
        user->is_away(true);
        if(!user_params.empty())
            user->set_away_mssg(user_params[0]);
        server->send_rpl("306", user, reply_params, "");
    }
}