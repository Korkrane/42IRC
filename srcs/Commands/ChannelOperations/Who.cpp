#include <IRC.hpp>

//TODO: a revoir (segfault) + codes a implementer
int    Commands::who_match_user(User *user, IRC *server)
{
    std::vector<User *> users = server->get_users();
    //std::vector<User *>::iterator it = users.begin();
    std::vector<std::string> params = user->get_params();
    server->send_rpl_display_all_users("352", user, user->_target_channel, "JOIN");
    return  (0);
}

void    Commands::who(User *user, IRC *server)
{
    (void)user;
    (void)server;

    who_match_user(user, server);
    return;
}